#pragma once

#include "Global.h"


/// ������� �������
enum  WantedLevel :
{
  Level_0 = 0u,
  Level_1 = 1u,
  Level_2 = 2u,
  Level_3 = 3u,
  Level_4 = 4u,
  Level_5 = 5u,
  Level_6 = 6u,
};


/// ������ �� �����. ���������� �����
enum  StarPolice:
{
  StarPolice_0 = 0u,                    ///< 0 �����
  StarPolice_1 = 600u,                  ///< ������ 1
  StarPolice_2 = 1600u,                 ///< ������ 2
  StarPolice_3 = 3000u,
  StarPolice_4 = 5000u,
  StarPolice_5 = 8000u,
  StarPolice_6 = 12000u,
};





class Player{

	private:

	public:
		Player();
		~Player();
};

