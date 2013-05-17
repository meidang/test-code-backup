//Identifies the type of information that will be written to the minidump file by the MiniDumpWriteDump function.
//标识由MiniDumpWriteDump函数写入到转储文件的信息类型
typedef enum _MINIDUMP_TYPE {
	//包括仅仅需要捕获过程中的所有现有线程的堆栈跟踪信息。
	MiniDumpNormal                         = 0x00000000,  
	//包括所有已加载的模块的数据段。这将导致在包括全局变量，它可以使小型转储文件的显着变大。每个模块控制，使用ModuleWriteDataSeg的的​​枚举值MODULE_WRITE_FLAGS。
	MiniDumpWithDataSegs                   = 0x00000001,  
	//包括所有访问内存中的进程。的原始存储器中的数据的结尾处有，使最初的结构可以被直接映射没有原料存储器信息。此选项可能会导致非常大的文件。
	MiniDumpWithFullMemory                 = 0x00000002,
	MiniDumpWithHandleData                 = 0x00000004,
	MiniDumpFilterMemory                   = 0x00000008,
	MiniDumpScanMemory                     = 0x00000010,
	MiniDumpWithUnloadedModules            = 0x00000020,
	MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
	MiniDumpFilterModulePaths              = 0x00000080,
	MiniDumpWithProcessThreadData          = 0x00000100,
	MiniDumpWithPrivateReadWriteMemory     = 0x00000200,
	MiniDumpWithoutOptionalData            = 0x00000400,
	MiniDumpWithFullMemoryInfo             = 0x00000800,
	MiniDumpWithThreadInfo                 = 0x00001000,
	MiniDumpWithCodeSegs                   = 0x00002000,
	MiniDumpWithoutAuxiliaryState          = 0x00004000,
	MiniDumpWithFullAuxiliaryState         = 0x00008000,
	MiniDumpWithPrivateWriteCopyMemory     = 0x00010000,
	MiniDumpIgnoreInaccessibleMemory       = 0x00020000,
	MiniDumpWithTokenInformation           = 0x00040000,
	MiniDumpValidTypeFlags                 = 0x0007ffff,
} MINIDUMP_TYPE;
