// 신호등 작동시간 출력용 매트릭스 핀 번호 배열
int PinRowFirst[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int PinColFirst[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
// 보행자 신호 출력용 매트릭스 핀 번호 배열
int PinRowSecond[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
int PinColSecond[] = { 23, 25, 27, 29, 31, 33, 35, 37 };

// 보행자 신호등 작동시간
#define WALKABLE_TIME 5
// 보행자 신호등 대기시간
#define WAIT_TIME 5

// 시간 간격 유지를 위한 변수들
unsigned timeFirst = 0;
unsigned timeLast = 0;
#define ONE_SECOND 1000

int numbers[10][8][4] =
{
  // ZERO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // ONE
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 1, 1, 1, 1 }
  },
  // TWO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },
  // THREE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // FOUR
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },
  // FIVE
  {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 1, 1, 1 }
  },
  // SIX
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // SEVEN
  {
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
  },
  // EIGHT
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // NINE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }
};

int signs[2][8][8] =
{
  // RED : CANNOT CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 }
  },
  // GREEN : CAN CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 }
  }
};

void clearFirst()
{
  for(int k = 0; k < 8; ++k)
  {
    digitalWrite(PinRowFirst[k], LOW);
    digitalWrite(PinColFirst[k], HIGH);
  }
}
void clearSecond()
{
  for(int k = 0; k < 8; ++k)
  {
    digitalWrite(PinRowSecond[k], LOW);
    digitalWrite(PinColSecond[k], HIGH);
  }
}

void displayNumbers(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    clearSecond();
    digitalWrite(PinRowSecond[r], HIGH);
    for(int c = 0; c < 4; ++c)
    {
      if(former[r][c]==1)
      {
        digitalWrite(PinColSecond[c], LOW);
      }
    }
    for(int c = 0; c < 4; ++c)
    {
      if(later[r][c]==1)
      {
        digitalWrite(PinColSecond[c+4], LOW);
      }
    }
    delay(1);
  }
}
void displaySigns(int signs[][8], int pinRow[], int pinCol[])
{
  for(int r = 0; r < 8; ++r)
  {
    if(pinRow[0] == 2)
    {
      clearFirst();
    }
    else
    {
      clearSecond();
    }
    digitalWrite(pinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(signs[r][c]==1)
      {
        digitalWrite(pinCol[c], LOW);
      }
    }
    delay(1);
  }
}

void canCross()
{
  for(int t = WALKABLE_TIME; t > -1; --t)
  {
    int FORM = t/10, LATE = t%10;
    timeFirst = millis();
    for(;;)
    {
      displaySigns(signs[1], PinRowSecond, PinColSecond);
      timeLast = millis();
      if(timeLast - timeFirst >= ONE_SECOND)
      {
        clearFirst();
        clearSecond();
        break;
      }
    }
  }
}
void waitCross()
{
  for(int t = WAIT_TIME; t > -1; --t)
  {
    int FORM = t/10, LATE = t%10;
    timeFirst = millis();
    for(;;)
    {
      displaySigns(signs[0], PinRowFirst, PinColFirst);
      displayNumbers(numbers[FORM], numbers[LATE]);
      timeLast = millis();
      if(timeLast - timeFirst >= ONE_SECOND)
      {
        clearFirst();
        clearSecond();
        break;
      }
    }
  }
}

void crosswalk()
{
  waitCross();
  canCross();
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; ++i)
  {
    pinMode(PinRowFirst[i], OUTPUT);
    pinMode(PinColFirst[i], OUTPUT);

    pinMode(PinRowSecond[i], OUTPUT);
    pinMode(PinColSecond[i], OUTPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  crosswalk();
}
