/******************************************************************************/

/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：CyDebug.h                                                        */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：20120529                                                         */
/*----------------------------------------------------------------------------*/
/* DSP -- 傅里叶变换                                                          */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */

/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/typedef.h"
#include "fft.h"
#include <math.h>
#include <stdlib.h>

#define FFT_SIZE  FRAME_SIZE             //定义傅里叶变换的点数

static CyINT16 lfftSize;

//制作规则:
//lTableCos:cos(2*pi*x/N);
//lTableSin:-sin(2*pi*x/N);
//其中pi为常数:3.141592;N:傅里叶变换的点数;x:0~N/2-1;  
static CyFLOAT lTableSin[FFT_SIZE/2+1];   //定义正弦表的存放空间
static CyFLOAT lTableCos[FFT_SIZE/2+1];   //定义余弦表的存放空间

/*******************************************************************
函数原型：struct CyComplex ComplexMulti(struct CyComplex b1,struct CyComplex b2)  
函数功能：对两个复数进行乘法运算
输入参数：两个以联合体定义的复数a,z2
输出参数：a和b的乘积，以联合体的形式输出
*******************************************************************/
static CyComplex ComplexMulti(CyComplex z1, CyComplex z2);


CyVOID InitFFT(CyINT16 fftsize)                     
{
	CyINT16 i;
	lfftSize = fftsize;

	if( fftsize!=FFT_SIZE )
	{
		CyTRACE("FFT.c InitFFT(), Size of FFT is not match!\n");
		exit(-1);
	}

	//制作规则:
	//lTableCos:cos(2*pi*x/N);
	//lTableSin:-sin(2*pi*x/N);
	//其中pi为常数:3.141592;N:傅里叶变换的点数;x:0~N/2-1;
	for(i=0; i<=fftsize/2; i++)
	{
// 		*(lTableCos+i) =  cos( _2PI*i/fftsize );
// 		*(lTableSin+i) = -sin( _2PI*i/fftsize );
		*(lTableCos+i) =  cos( _PI/(CyFLOAT)i );
		*(lTableSin+i) = -sin( _PI/(CyFLOAT)i );
	}
}

CyVOID FFT(CyComplex *z, CyINT16 N)
{
	CyINT16 f,m,nv2,nm1,i,k,l,j=0;
	CyComplex u,w,t;
	
	nv2 = N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
	nm1 = N-1;  
	for(i=0;i<nm1;i++)        
	{
		if(i<j)                    //如果i<j,即进行变址
		{
			t=z[j];           
			z[j]=z[i];
			z[i]=t;
		}
		k=nv2;                    //求j的下一个倒位序
		while(k<=j)               //如果k<=j,表示j的最高位为1   
		{           
			j=j-k;                 //把最高位变成0
			k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
		}
		j=j+k;                   //把0改为1
	}
	
	{
		CyINT16 le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
		f=N;
		for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
			;        // N=2**l;
		for(m=1;m<=l;m++)                         // 控制蝶形结级数
		{                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
			le=1<<m;                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
			lei=le/2;                               //同一蝶形结中参加运算的两点的距离
			u.real=1.0;                             //u为蝶形结运算系数，初始值为1
			u.imag=0.0;
			//u = {1.0f, 0.0f};
			//w.real=cos(_PI/lei);                  //不适用查表法计算sin值和cos值
			//w.imag=-sin(_PI/lei);
			w.real=lTableCos[lei];                  //不适用查表法计算sin值和cos值
			w.imag=lTableSin[lei];
			for(j=0;j<=lei-1;j++)                  //控制计算不同种蝶形结，即计算系数不同的蝶形结
			{
				for(i=j;i<N;i=i+le)           //控制同一蝶形结运算，即计算系数相同蝶形结
				{
					ip=i+lei;                          //i，ip分别表示参加蝶形运算的两个节点
					t=ComplexMulti(z[ip],u);                   //蝶形运算，详见公式
					z[ip].real=z[i].real-t.real;
					z[ip].imag=z[i].imag-t.imag;
					z[i].real=z[i].real+t.real;
					z[i].imag=z[i].imag+t.imag;
				}
				u=ComplexMulti(u,w);                          //改变系数，进行下一个蝶形运算
			}
		}
	}
}


CyComplex ComplexMulti(CyComplex z1, CyComplex z2)      
{
	CyComplex res;
	res.real=z1.real*z2.real-z1.imag*z2.imag;
	res.imag=z1.real*z2.imag+z1.imag*z2.real;
	return res;
}


CyVOID RealFFT(CyFLOAT *data, CyINT16 N)
{
	CyComplex fftData[FFT_SIZE];
	CyINT16 i;

	// Step 1: 转换成复数，其虚部为0
	for (i=0; i<N; i++)
	{
		fftData[i].real = data[i];
		fftData[i].imag = 0.0f;
	}

	// Step 2: 复数傅里叶变换
	FFT(fftData, N);

	// Step 3: 计算能量值
	for(i=0; i<N/2; i++)
	{
		data[i] = fftData[i].real*fftData[i].real+fftData[i].imag*fftData[i].imag;
	}
}