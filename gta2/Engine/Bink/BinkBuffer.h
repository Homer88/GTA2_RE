#ifndef ___BINKBUFFER__H__
#define ___BINKBUFFER__H__

class BinkBuffer{
	public:
		bool Status;
		BinkBuffer();
		~BinkBuffer();
		void Open();
		void Close();
	
};

extern BinkBuffer gBinkBuffer;

#endif