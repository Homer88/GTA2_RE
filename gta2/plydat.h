#ifndef __PLAYDAT_H_
#define __PLAYDAT_H_
#include <new> 
class PlayerData {
public:
	int field;
	int field_4;
	int field_8;
	int field_C;
	short field_10;
	char  gap12[6090];
	char field_17DC;
	char field_17DD;
	char field_17DE;
	char field_17DF;
	char field_17E0;
	char field_17E1;
	char field_17E2;
	char field_17E3;
	char field_17E4;
	char field_17E5;
	char field_17E6;
	char field_17E7;
	char field_17E8;
	char field_17E9;
	char field_17EA;
	char field_17EB;
	char field_17EC;
	char field_17ED;
	char field_17EE;
	char field_17EF;
	char field_17F0;
	char field_17F1;
	char field_17F2;
	char field_17F3;
	char field_17F4;
	char field_17F5;
	char field_17F6;
	char field_17F7;
	char field_17F8;
	char field_17F9;
	char field_17FA;
	char field_17FB;
	char field_17FC;
	char field_17FD;
	char field_17FE;
	char field_17FF;
	byte arr_0x28[40];
	byte gap1828[48];
	char field_1858;
	char field_1859;
	char field_185A;
	char field_185B;
	char field_185C;
	char field_185D;
	char field_185E;
	char field_185F;
	char field_1860;
	char field_1861;
	char field_1862;
	char field_1863;
	char field_1864;
	char field_1865;
	char field_1866;
	char field_1867;
	char field_1868;
	char field_1869;
	char field_186A;
	char field_186B;
	char field_186C;
	char field_186D;
	char field_186E;
	char field_186F;
	char field_1870;
	char field_1871;
	char field_1872;
	char field_1873;
	char field_1874;
	char field_1875;
	char field_1876;
	char field_1877;
	char field_1878;
	char field_1879;
	char field_187A;
	char field_187B;
	char field_187C;
	char field_187D;
	char field_187E;
	char field_187F;
	char field_1880;
	char field_1881;
	char field_1882;
	char field_1883;
	char field_1884;
	char field_1885;
	char field_1886;
	//S151 S151_arr[12];
	//S151 S151;
	//S151 S151_1;
	//S151* S151_2;
	byte gap25B4[48];
	char field_25E4;
	byte gap25E5[26];
	char field_25FF;
	byte gap2600[26];
	char field_261A;
	byte gap261B[20];
	char field_262F;
	byte gap2630[26];
	char field_264A;
	byte gap264B[50];
	char field_267D;
	byte gap267E[29];
	char field_269B;
	byte gap269C[2];
	char field_269E;
	char field_269F;
	//PlaySlot PlayerSlotSave[8];
	// 
	 // —татический метод создани€
	static PlayerData* Create(void* pMemory) {
		return new (pMemory) PlayerData;
	}
		PlayerData();
		// явный деструктор
		void Destroy() {
			this->~PlayerData();
		}
};

#endif // !__PLAYDAT_H_

