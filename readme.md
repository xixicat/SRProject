-----------------------------------------------------------------------------
SRParamSet: 系统参数配置和数据结构的定义
- asrconfig.h: 语音识别的一些参数设置
- CyDebug.h: 用于编译和调试，中间结果输出
- CyMath.h: 数学函数接口，可以自己编写高效率的数学函数
- datadef[.h, .c]: 语音缓冲区和特征向量、特征序列等数据结构的定义
- nlpgmm.h: NLP+GMM的数据结构定义
- typedef.h: 基本数据类型的定义
- options.h: 参数选项定义
{ SRParameterSet.c }: 参数配置模块测试代码


-----------------------------------------------------------------------------
DSP: 数字信号处理模块
- 依赖关系： <SRParamSet>
- fft[.h, .c] : 傅里叶变换
{ dspMain.c }: fft变换测试代码



-----------------------------------------------------------------------------
FeatureExtraction: 特征提取模块
- 依赖关系： <SRParamSet>, <DSP>
- FeatureExtraction[.h, .c]: 特征提取模块，模块的外部接口
- DeltaFeature[.h, .c]: 动态特征参数
- MFCC[.h, .c]: 基本MFCC参数提取
- FeatureTransform[.h, .c]: 特征变化(CMVN, CMS)
{ FeatureExtractionMain.c } : 模块测试代码



-----------------------------------------------------------------------------
LoadNlpGmm: 从模型文件将模型加载到内存
- 依赖关系： <SRParamSet>
- LoadNlpGmm[.h, .c]: 加载模型参数
{ loadNlpGmm_Main.c } : 模块测试代码



-----------------------------------------------------------------------------
NlpGmmModelEval : 输入特征序列和模型集，找出最佳的匹配模型
依赖关系： <SRParamSet>
nlpgmmRecognition[.h, .c]: 识别代码
{ nlpGMM_main.c } : 模块测试代码



-----------------------------------------------------------------------------
NonLinearPartition: 对特征序列进行非线性分段
- 依赖关系： <SRParamSet>
- nlp[.h, .c]: 非线性分段
{ nlpMain.c } : 模块测试代码


-----------------------------------------------------------------------------
RealTimeFrontEnd: 实时前端处理，包括端点检测，并提取特征
- 依赖关系： <SRParamSet>, <FeatureExtraction>
- realtimefrontend[.h, .c]: 前端处理，外部接口
- vad[.h, .c]: 端点检测
- dspAIC[.h, .c]: dsp外部函数采集接口
- common[.h, .c]: 一些全局变量和公有数据项定义
{ main.c } : 模块测试代码



-----------------------------------------------------------------------------
SpeechCollection: MFC语音采集程序
......



-----------------------------------------------------------------------------
SRControl: 语音识别控制主程序，识别入口主程序
- 依赖关系： <SRParamSet>, <SpeechCollection>, <RealTimeFrontEnd>,
                 <LoadNlpGmm>, <NlpGmmModelEval>, <NonLinearPartition>
- SRControl[.h, .cpp]: 控制主程序
- wrapper[.h, .c]: C++包装程序，做成标准C语言接口，方便调用
