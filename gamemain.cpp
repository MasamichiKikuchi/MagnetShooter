#include	"DxLib.h"
#include <math.h>
//
// �萔�E�\���̒�`
//

// �`�b�v�̃T�C�Y
#define	CHIP_W		(64)
#define	CHIP_H		(64)

// �}�b�v�̃T�C�Y
#define	MAP_W		(30)
#define	MAP_H		(17)

#define STAGE_MAX (3)
// ���̃A�j���[�V�����̃t���[����
#define	ANIME_FRAME	(5)

// 4������`
#define	ARROW_DN	(0)	// ��
#define	ARROW_LF	(1)	// ��
#define	ARROW_RI	(2)	// �E
#define	ARROW_UP	(3)	// ��

#define	OP_WORDS	(19) //�I�[�v�j���O�p�[�g�̃Z���t��
#define	ED_WORDS	(10) //�G���f�B���O�p�[�g�̃Z���t��

// ���̈ʒu�������\����
struct POSITION
{
	int	x;
	int y;
};

//
// �O���[�o���ϐ��錾
//

// �}�b�v�f�[�^
int	map[MAP_W * MAP_H]; 
int box[MAP_W * MAP_H];

// �A�j���[�V�����p�̃{�[�h
int gAnimeBoard[MAP_W * MAP_H];	

// �X�e�[�W�f�[�^(map��box��player�ʒu������������)
// 0:��, 1:player, 2:�����Ɣ�Ԕ�, 3:�P�}�X������,4:�S�[���n�_, 6�`9:��,10�ȏ�F��
int stage[STAGE_MAX][MAP_W * MAP_H] ={
{
    //STAGE1
	24,24,23,24,24,23,24,24,25,24,24,24,25,23,25,24,23,23,24,25,24,25,23,24,23,24,23,24,25,25,
    25,25,25,23,23,24,23,23,24,23,24,24,23,25,25,24,24,23,25,24,23,24,25,25,25,24,25,23,23,23,
    24,24,24,25,25,25,25,25,23,14,22,22,22,17,23,25,25,25,14,22,17,25,25,24,24,25,24,23,25,23,
    23,25,24,25,24,24,23,25,23,14,1,3,6,22,22,22,22,22,22,4,17,25,23,23,25,25,25,25,25,24,
    25,24,24,23,25,23,24,24,23,14,6,6,6,6,6,6,6,6,6,6,17,25,24,25,23,25,23,23,24,25,
    24,23,23,25,25,25,25,24,23,14,6,6,6,6,6,6,6,6,6,6,17,24,23,24,24,23,25,25,25,24,
    23,24,25,24,25,23,24,25,23,14,6,6,6,10,19,19,19,19,19,19,18,24,25,23,24,23,24,24,23,25,
    23,23,24,23,23,25,23,23,24,14,6,6,6,17,23,25,23,25,24,24,25,24,24,24,24,25,25,23,25,23,
    25,25,25,24,23,24,25,23,25,14,6,6,6,17,25,24,24,24,24,23,24,24,25,23,24,24,24,25,25,25,
    23,24,24,25,23,23,25,23,23,14,6,6,6,17,25,23,24,24,25,24,24,24,24,24,24,24,24,25,23,24,
    24,25,25,24,24,23,25,25,24,14,6,6,2,17,23,25,24,24,25,24,23,23,23,25,23,23,25,23,25,25,
    25,23,24,24,25,25,24,23,23,14,6,6,6,17,24,23,24,23,23,25,25,25,25,23,23,25,25,25,24,25,
    23,25,24,23,24,24,23,25,24,15,19,19,19,18,23,25,23,23,23,24,24,23,23,25,25,23,25,23,23,23,
    25,24,23,25,23,25,25,25,23,25,23,23,24,25,25,24,23,23,23,23,23,24,23,25,23,23,25,25,24,25,
    23,24,23,24,23,25,23,23,23,25,23,24,24,24,23,23,23,25,24,23,23,25,23,24,23,23,25,24,24,23,
    24,23,25,25,25,25,25,24,23,24,23,23,25,23,23,23,25,23,24,23,24,23,25,24,24,23,25,23,23,24,
    24,25,24,23,25,23,25,23,24,23,24,25,23,23,25,24,23,23,24,24,23,23,25,23,25,25,23,24,25,24,
},

{
	//STAGE2
	24,23,23,24,14,22,22,22,22,22,22,24,25,23,24,24,23,24,25,25,23,22,22,22,22,17,23,23,23,24,
	25,24,23,23,14,6,6,6,6,6,6,22,25,25,25,24,24,24,24,23,22,6,26,6,1,17,23,25,24,23,
	23,25,24,24,14,6,6,6,6,6,6,6,22,22,22,22,22,22,22,22,6,6,26,2,6,17,25,25,25,24,
	24,25,23,24,14,6,6,6,6,6,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,17,23,25,24,24,
	23,23,24,23,15,19,11,6,6,6,26,6,6,6,6,6,6,6,6,26,6,6,3,6,6,17,23,25,23,24,
	23,24,24,23,23,24,14,6,6,6,6,6,6,6,6,6,6,6,6,26,6,6,6,6,6,17,25,25,23,23,
	23,24,24,23,24,23,14,6,6,3,6,6,26,26,26,6,6,6,6,6,26,6,6,6,6,17,24,25,24,25,
	25,24,25,24,23,24,14,6,6,3,6,6,26,4,26,6,6,6,6,6,26,6,6,6,6,17,25,25,24,23,
	24,24,23,24,23,23,14,6,6,6,6,6,26,6,26,6,6,6,6,6,26,6,6,6,6,17,25,25,25,25,
	25,23,23,23,25,24,14,6,6,6,6,6,26,6,6,6,6,6,6,6,26,6,6,6,6,17,23,25,24,23,
	24,24,24,25,23,24,14,6,6,6,6,6,26,6,6,6,6,6,26,6,26,6,6,6,6,17,25,25,24,23,
	23,23,25,23,24,24,14,6,6,6,6,6,26,26,26,26,26,26,26,26,26,6,6,6,6,17,23,23,24,25,
	23,25,23,25,14,22,22,6,6,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,23,23,25,25,
	24,25,25,25,14,6,6,6,6,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,26,17,23,24,24,25,
	23,23,25,24,14,6,6,6,6,6,6,6,10,19,19,19,19,19,19,11,6,6,6,26,26,17,23,24,23,23,
	25,23,23,23,14,6,6,6,6,6,6,10,18,24,25,24,23,25,25,15,11,6,6,6,10,18,24,24,24,24,
	25,25,23,24,15,19,19,19,19,19,19,18,23,24,25,25,23,23,25,25,15,19,19,19,18,23,25,23,23,24,
},
{
	//STAGE3
	25,24,25,23,14,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,17,
	24,25,24,25,14,6,6,6,6,6,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,
	25,24,23,23,14,6,6,6,6,6,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,10,18,
	23,24,24,24,14,6,6,6,6,6,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,24,
	25,23,24,23,14,6,6,6,6,6,26,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,24,
	25,25,14,22,22,6,6,6,6,6,26,26,26,6,6,6,6,6,6,6,6,6,26,26,6,6,6,6,17,23,
	23,23,14,6,6,6,6,6,26,1,26,26,26,6,6,6,6,3,3,3,6,26,6,6,6,6,6,26,17,23,
	23,25,14,6,6,6,6,6,2,6,26,4,6,6,6,6,6,6,6,6,6,26,6,6,6,6,6,6,17,25,
	25,24,14,6,6,6,6,6,26,6,26,26,26,6,6,6,6,3,3,3,6,6,6,6,6,6,6,6,17,25,
	24,23,14,6,6,6,6,6,6,6,26,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,23,
	23,24,14,6,6,6,6,6,6,6,26,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,24,
	25,24,14,6,6,6,6,6,6,6,6,6,6,26,26,6,6,6,6,6,6,6,6,6,6,6,6,6,17,24,
	24,23,14,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,17,23,
	24,24,14,6,6,6,6,6,6,6,6,6,6,6,6,10,19,19,19,19,11,6,6,6,6,6,6,6,17,24,
	23,14,22,6,6,6,26,6,6,6,6,6,6,6,6,17,24,25,24,23,14,6,6,6,6,6,6,26,22,17,
	23,14,6,6,26,6,6,6,26,26,6,6,6,6,6,17,25,24,24,24,14,6,6,6,6,6,6,6,6,17,
	24,15,19,19,19,19,19,19,19,19,19,19,19,19,19,18,25,24,24,25,15,19,19,19,19,19,19,19,19,18,
},
};

int count[STAGE_MAX] = {
	//STAGE1
	3,
	//STAGE2
	7,
	//STAGE3
	13,
};

// ��̕ۑ��f�[�^�i�}�b�v�{�v���C���[�ʒu�j
int stepsave_map[MAP_W * MAP_H];
int stepsave_box[MAP_W * MAP_H];
int stepsave_playerX;
int stepsave_playerY;
int countSave;

//�����������
int countInstage;



// �摜�f�[�^
int cgChip[99];		// �`�b�v�摜�i�z��j
int cgPlayer[3 * 4];		// �v���C���[
int cgBox[2];		// ��(�ړ��I�u�W�F�N�g�j
int cgTitle;
int cgManual;
int cgCount[30];
int cgCountBase;
int cgCountBaseBob;
int cgOpMainCharacter[OP_WORDS];
int cgSubCharacter[OP_WORDS];
int cgOpWords[OP_WORDS];
int cgOpName[OP_WORDS];
int opBack;
int cgClear;
int cgGameOver;

int cgEdMainCharacter[OP_WORDS];
int cgEdSubCharacter[OP_WORDS];
int cgEdWords[ED_WORDS];
int cgEdName[ED_WORDS];
int cgEdBack;
int cgBlackBuck;
int cgWhiteBuck;
int howToPlay;//�V�ѕ�

int cgPlayerShadow;
int cgObjectShadow;
int cgObject[2];	

int cgEnd;


// �Q�[�����
int gKey;			// �L�[���͂̏��
int gTrg;			// �g���K���͂̏��

// �v���C���[���
int playerX, playerY;	// ���W�i�`�b�v�P�ʁj
int	arrow;		// �����Ă������
int boxType;

//�V�[���J��
int title; //�^�C�g���̃t���O
int menu; //���j���[��ʂ̃t���O
int gameOver; //�Q�[���I�[�o�[�̃t���O
int stageClear; //�N���A���o�̃t���O
int op; //�N���A���o�̃t���O
int game; //�Q�[����ʂ̃t���O
int ed; //�G���f�B���O�̃t���O

//�X�e�[�W�̔ԍ�
int stageNo;

// �A�j���[�V�����֘A
int gAnimeCnt;			// �A�j���[�V�����̃J�E���g
int animcnt;	// �A�j���[�V�����J�E���^
int playerAnimspeed = 10;
int objectAnimspeed = 20;
//�A�h�x���`���[�p�[�g�֘A
int wordNum;
int edWordNum;
//�f�o�b�O�p
int boxX;
int boxY;
int push;
int nextX;
int nextY;
int moveX;
int moveY;
int goalX;
int goalY;

static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS


void StageInit(int stageNo) {

	stageClear = 0;
	//�X�e�[�W���̏�����
	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			
			box[y * MAP_W + x] = 0;					
			map[y * MAP_W + x] = 0;				
		}
	}


	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// stage[stageNo][] ����A�`�b�v�ԍ������o��
			// 0�ȉ�:��, 1:player, 2:�����Ɣ�Ԕ�, 3:�P�}�X������,4:�S�[���n�_, 6�ȏ�:��
			int chip_no = stage[stageNo][y * MAP_W + x];
			// box[]�̏�������
			box[y * MAP_W + x] = 0;
			if (chip_no == 2) { box[y * MAP_W + x] = 1; }
			if (chip_no == 3) { box[y * MAP_W + x] = 2; }
			// map[]�̏�������
			map[y * MAP_W + x] = 0;
			if (chip_no == 6) { map[y * MAP_W + x] = 0; }   // ��
			if (chip_no == 0) { map[y * MAP_W + x] = 1; }   // ��
			if (chip_no == 4) { map[y * MAP_W + x] = 2; }	// �S�[���n�_
			if (chip_no == 10) { map[y * MAP_W + x] = 10; }
			if (chip_no == 11) { map[y * MAP_W + x] = 11; }
			if (chip_no == 12) { map[y * MAP_W + x] = 12; }
			if (chip_no == 13) { map[y * MAP_W + x] = 13; }
			if (chip_no == 14) { map[y * MAP_W + x] = 14; }
			if (chip_no == 15) { map[y * MAP_W + x] = 15; }
			if (chip_no == 16) { map[y * MAP_W + x] = 16; }
			if (chip_no == 17) { map[y * MAP_W + x] = 17; }
			if (chip_no == 18) { map[y * MAP_W + x] = 18; }
			if (chip_no == 19) { map[y * MAP_W + x] = 19; }
			if (chip_no == 20) { map[y * MAP_W + x] = 20; }
			if (chip_no == 21) { map[y * MAP_W + x] = 21; }
			if (chip_no == 22) { map[y * MAP_W + x] = 22; }
			if (chip_no == 23) { map[y * MAP_W + x] = 23; }
			if (chip_no == 24) { map[y * MAP_W + x] = 24; }
			if (chip_no == 25) { map[y * MAP_W + x] = 25; }
			if (chip_no == 26) { map[y * MAP_W + x] = 26; }

			if (chip_no == 1) {
				// �����Ƀv���C���[���W��ݒ�
				map[y * MAP_W + x] = 0;
				playerX = x;
				playerY = y;
			}
		}
	}
	countInstage = count[stageNo];
}

// 1��ۑ�����֐�
void SaveOneStep() {
	// stepsave �ɁA�����ۑ�
	for (int n = 0; n < MAP_W * MAP_H; n++) {
		stepsave_map[n] = map[n];
		stepsave_box[n] = box[n];
	}
	stepsave_playerX = playerX;
	stepsave_playerY = playerY;
	countSave = countInstage;
}

// 1��߂��֐�
void BackOneStep() {
	// stepsave ���A����ɃR�s�[
	for (int n = 0; n < MAP_W * MAP_H; n++) {
		map[n] = stepsave_map[n];
		box[n] = stepsave_box[n];
	}
	playerX = stepsave_playerX;
	playerY = stepsave_playerY;
	countInstage = countSave;
}

//�I�u�W�F�N�g�̈ʒu���擾
POSITION GetBoxPos()
{
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{

			if (box[y * MAP_W + x] == 1)
			{
				POSITION pos;
				pos.x = x;
				pos.y = y;
				return pos;
			}
		}
	}
}

//���BOX���Z�b�g
void SetBox(int x, int y, int state)
{
	box[y * MAP_W + x] = state;
}

// �A�j���[�V�����̍ő�ԍ����擾
int GetAnimeMax()
{
	int number = 0;
	int x, y;
	int i = 0;

	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			
			int n = gAnimeBoard[y * MAP_W + x];

			if (n != 0 && n > number) {
				number = n;
			}
		}
	}
	return number;
}

// ���̃A�j���[�V�������Z�b�g����
// ����:
//   x = ����X
//   y = ����Y
//   set = 0:�A�j���[�V��������, 1:�A�j���[�V�����̏��Ԃ��Z�b�g
void SetAnime(int x, int y, int set)
{	
		int number = 0;

		if (set == 1)
		{
			number = GetAnimeMax();
			number++;
		}
		gAnimeBoard[y * MAP_W + x] = number;	
}


//�A�j���[�V�����̏ꏊ���擾
POSITION GetAnimePos()
{
	POSITION pos = { -1, -1 };
	int number = GetAnimeMax();

	// �A�j���[�V�����͖���
	if (number == 0) {
		return pos;
	}

	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			int n = gAnimeBoard[y * MAP_W + x];
			// 1�Ԕԍ����������ꏊ���擾
			if (n != 0 && n <= number) {
				number = n;
				pos.x = x;
				pos.y = y;
			}
		}
	}
	return pos;
}

// �A�j���[�V��������
void AnimeProcess()
{
	gAnimeCnt++;
	// ANIME_FRAME���� 1 �R�}�����������Ă���
	if (gAnimeCnt >= ANIME_FRAME) {
		gAnimeCnt = 0;

		// �A�j���[�V��������R�}���擾
		POSITION pos = GetAnimePos();

		if (pos.x >= 0 && pos.y >= 0)
		{
			POSITION nowpos = GetBoxPos();	
			
			// �����Z�b�g���ăA�j���[�V����������
			SetBox(nowpos.x, nowpos.y, 0);
			SetAnime(nowpos.x, nowpos.y, FALSE);
			SetBox(pos.x, pos.y, 1);			
			SetAnime(pos.x, pos.y, FALSE);
		}
	}
}

bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit() {
	// �摜�̓ǂݍ���
	//�}�b�v�֌W
	cgChip[0] = LoadGraph("res/����.png");
	cgChip[1] = LoadGraph("res/���� ����.png");
	cgChip[2] = LoadGraph("res/�S�[�� �i���j�����ς�.png");
	cgChip[3] = LoadGraph("res/dot.png");
	cgChip[10] = LoadGraph("res/�ǃp�^�[��1.png");
	cgChip[11] = LoadGraph("res/�ǃp�^�[��2 .png");
	cgChip[12] = LoadGraph("res/�ǃp�^�[��3 .png");
	cgChip[13] = LoadGraph("res/�ǃp�^�[��4 .png");
	cgChip[14] = LoadGraph("res/�ǉE .png");
	cgChip[15] = LoadGraph("res/�ǉE�� .png");
	cgChip[16] = LoadGraph("res/�ǉ� .png");
	cgChip[17] = LoadGraph("res/�Ǎ� .png");
	cgChip[18] = LoadGraph("res/�Ǎ��� .png");
	cgChip[19] = LoadGraph("res/�Ǐ� .png");
	cgChip[20] = LoadGraph("res/�Ǒ���normal.png");
	cgChip[21] = LoadGraph("res/�Ǒ��ʓd�C����.png");
	cgChip[22] = LoadGraph("res/�Ǒ��ʓd�C�Ȃ�.png");
	cgChip[23] = LoadGraph("res/�F���p�^�[��1.png");
	cgChip[24] = LoadGraph("res/�F���p�^�[��2.png");
	cgChip[25] = LoadGraph("res/�F���p�^�[��3.png");
	cgChip[26] = LoadGraph("res/���u���b�N.png");
	
	//�L�����N�^�[�A�I�u�W�F�N�g
	LoadDivGraph("res/�X���C�h1.�摜�؂蔲��touka.png", 3 * 4, 3, 4, 64, 64, cgPlayer);
	LoadDivGraph("res/robot1.png", 2, 2, 1, 64, 64, cgObject);
	cgPlayerShadow = LoadGraph("res/�e.png");
	cgObjectShadow = LoadGraph("res/�etouka.png");
	cgBox[0] = LoadGraph("res/bloc.png");
	cgBox[1] = LoadGraph("res/robo (1).png");
	
	//�������
	cgCountBase = LoadGraph("res/�f��.png");
	cgCountBaseBob = LoadGraph("res/�f������300.png");
	cgCount[1] = LoadGraph("res/1_red_white.png");
	cgCount[2] = LoadGraph("res/2_red_white.png");
	cgCount[3] = LoadGraph("res/3_red_white.png");
	cgCount[4] = LoadGraph("res/4_green.png");
	cgCount[5] = LoadGraph("res/5_green.png");
	cgCount[6] = LoadGraph("res/6_green.png");
	cgCount[7] = LoadGraph("res/7_green.png");
	cgCount[8] = LoadGraph("res/8_green.png");
	cgCount[9] = LoadGraph("res/9_green.png");
	cgCount[10] = LoadGraph("res/10_green.png");
	cgCount[11] = LoadGraph("res/11_green.png");
	cgCount[12] = LoadGraph("res/12_green.png");
	cgCount[13] = LoadGraph("res/13_green.png");
	cgCount[14] = LoadGraph("res/14_green.png");
	cgCount[15] = LoadGraph("res/15_green.png");
	//�e���o�̉摜
	cgClear = LoadGraph("res/CLEAR.png");
	cgGameOver = LoadGraph("res/GAME OVER.png");
	cgEnd = LoadGraph("res/�����܂�.png");
	howToPlay = LoadGraph("res/�v���[���e�[�V����3.png");
	cgTitle = LoadGraph("res/title.png");
	cgManual = LoadGraph("res/�������ق��ق�.png");

	//�I�[�v�j���O�֘A
	//��l���̉摜[0]�͂���Ȃ�
	cgOpMainCharacter[1] = LoadGraph("");
	cgOpMainCharacter[2] = LoadGraph("");
	cgOpMainCharacter[3] = LoadGraph("");
	cgOpMainCharacter[4] = LoadGraph("");
	cgOpMainCharacter[5] = LoadGraph("res/�l�b�g�N(����).png");
	cgOpMainCharacter[6] = LoadGraph("res/�l�b�g�N(����).png");
	cgOpMainCharacter[7] = LoadGraph("res/�l�b�g�N(�Ί�).png");
	cgOpMainCharacter[8] = LoadGraph("res/�l�b�g�N(�Ί�).png");
	cgOpMainCharacter[9] = LoadGraph("res/�l�b�g�N(�^��).png");
	cgOpMainCharacter[10] = LoadGraph("res/�l�b�g�N(�^��).png");
	cgOpMainCharacter[11] = LoadGraph("res/�l�b�g�N(�s�@��).png");
	cgOpMainCharacter[12] = LoadGraph("res/�l�b�g�N(�s�@��).png");
	cgOpMainCharacter[13] = LoadGraph("res/�l�b�g�N(����).png");
	cgOpMainCharacter[14] = LoadGraph("res/�l�b�g�N(����).png");
	cgOpMainCharacter[15] = LoadGraph("res/�f�t�H�����l�b�g�N(����).png");
	cgOpMainCharacter[16] = LoadGraph("res/�f�t�H�����l�b�g�N(����).png");
	cgOpMainCharacter[17] = LoadGraph("res/�f�t�H�����l�b�g�N(�Ί�).png");

	//�T�u�L�����N�^�[�̉摜[0]�͂���Ȃ�
	cgSubCharacter[1] = LoadGraph("");
	cgSubCharacter[2] = LoadGraph("");
	cgSubCharacter[3] = LoadGraph("");
	cgSubCharacter[4] = LoadGraph("");
	cgSubCharacter[5] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[6] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[7] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[8] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[9] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[10] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[11] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[12] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[13] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[14] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[15] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[16] = LoadGraph("res/���m�����Gtouka.png");
	cgSubCharacter[17] = LoadGraph("res/���m�����Gtouka.png");
	//�Z���t�摜�@[0]�͂���Ȃ�
	cgOpWords[1] = LoadGraph("");
	cgOpWords[2] = LoadGraph("res/�X���C�h2.PNG");//�h�J�[��
	cgOpWords[3] = LoadGraph("res/�X���C�h2.toukapng.png");
	cgOpWords[4] = LoadGraph("res/�X���C�h3 kirinuki.PNG");
	cgOpWords[5] = LoadGraph("res/�X���C�h4 kirinuki.PNG");
	cgOpWords[6] = LoadGraph("res/�X���C�h5 kirinuki.PNG");
	cgOpWords[7] = LoadGraph("res/�X���C�h6 kirinuki.PNG");
	cgOpWords[8] = LoadGraph("res/�X���C�h7 kirinuki.PNG");
	cgOpWords[9] = LoadGraph("res/�X���C�h8 kirinuki.png");
	cgOpWords[10] = LoadGraph("res/�X���C�h9 kirinuki.PNG");
	cgOpWords[11] = LoadGraph("res/�X���C�h10 kirinuki.PNG");
	cgOpWords[12] = LoadGraph("res/�X���C�h11 kirinuki.PNG");
	cgOpWords[13] = LoadGraph("res/�X���C�h12 kirinuki.PNG");
	cgOpWords[14] = LoadGraph("res/�X���C�h13 kirinuki.PNG");
	cgOpWords[15] = LoadGraph("res/�X���C�h13 kirinuki.PNG");
	cgOpWords[16] = LoadGraph("res/�X���C�h14 kirinuki.PNG");
	cgOpWords[17] = LoadGraph("res/�X���C�h15 kirinuki.PNG");

	//�L�����N�^�[���\���@[0]�͂���Ȃ�
	cgOpName[1] = LoadGraph("");
	cgOpName[2] = LoadGraph("");
	cgOpName[3] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[4] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[5] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[6] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[7] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[8] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[9] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[10] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[11] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[12] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[13] = LoadGraph("");
	cgOpName[14] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[15] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgOpName[16] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgOpName[17] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	//�w�i
	opBack = LoadGraph("res/utyuusen haikei kannsei 1.jpg");
	//�Z���t�ԍ�
	wordNum = 0;

	//�G���f�B���O�֘A
	//��l���̉摜
	cgEdMainCharacter[0] = LoadGraph("res/�l�b�g�N(�Ί�).png");
	cgEdMainCharacter[1] = LoadGraph("res/�l�b�g�N(�Ί�).png");
	cgEdMainCharacter[2] = LoadGraph("res/�l�b�g�N(����).png");
	cgEdMainCharacter[3] = LoadGraph("res/�l�b�g�N(�^��).png");
	cgEdMainCharacter[4] = LoadGraph("res/�l�b�g�N(����).png");
	cgEdMainCharacter[5] = LoadGraph("");
	cgEdMainCharacter[6] = LoadGraph("");
	cgEdMainCharacter[7] = LoadGraph("");
	cgEdMainCharacter[8] = LoadGraph("");
	cgEdMainCharacter[9] = LoadGraph("");

	//�T�u�L�����N�^�[�̉摜
	cgEdSubCharacter[0] = LoadGraph("res/���m�g.png");
	cgEdSubCharacter[1] = LoadGraph("res/���m�g.png");
	cgEdSubCharacter[2] = LoadGraph("res/���m�g.png");
	cgEdSubCharacter[3] = LoadGraph("res/���m�g.png");
	cgEdSubCharacter[4] = LoadGraph("res/���m�g.png");
	cgEdSubCharacter[5] = LoadGraph("");
	cgEdSubCharacter[6] = LoadGraph("");
	cgEdSubCharacter[7] = LoadGraph("");
	cgEdSubCharacter[8] = LoadGraph("");
	cgEdSubCharacter[9] = LoadGraph("");
	//�Z���t�摜
	cgEdWords[0] = LoadGraph("res/�X���C�h16 kirinuki.PNG");
	cgEdWords[1] = LoadGraph("res/�X���C�h17 kirinuki.PNG");
	cgEdWords[2] = LoadGraph("res/�X���C�h18 kirinuki.PNG");
	cgEdWords[3] = LoadGraph("res/�X���C�h19 kirinuki.PNG");
	cgEdWords[4] = LoadGraph("res/�X���C�h20 kirinuki.PNG");
	cgEdWords[5] = LoadGraph("");
	cgEdWords[6] = LoadGraph("res/�X���C�h21 kirinuki.PNG");
	cgEdWords[7] = LoadGraph("res/�X���C�h22 kirinuki.PNG");
	cgEdWords[8] = LoadGraph("res/�X���C�h23 kirinuki.PNG");
	cgEdWords[9] = LoadGraph("res/�X���C�h24 kirinuki.PNG");


	//�L�����N�^�[���\���@
	cgEdName[0] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgEdName[1] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgEdName[2] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgEdName[3] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgEdName[4] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgEdName[5] = LoadGraph("");
	cgEdName[6] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgEdName[7] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");
	cgEdName[8] = LoadGraph("res/���m�@���O�@�w�i����.png");
	cgEdName[9] = LoadGraph("res/�l�b�g����@���O�@�w�i����.png");

	//�w�i
	cgEdBack = LoadGraph("res/�w�i�@�F���D���Q.jpg");
	cgBlackBuck = LoadGraph("res/blak.png");
	cgWhiteBuck = LoadGraph("res/white.png");
	
	//�Z���t�ԍ�
	edWordNum = 0;

	// �v���C���[���̏�����
	playerX = 2;
	playerY = 2;

	//�V�[���J�ڃt���O
	title = 1;
	menu = 0;
	gameOver = 0;

	//�X�e�[�W�ԍ�
	stageNo = 0;
	
	//�L�����N�^�[�̃A�j���[�V�������x
	gAnimeCnt = 0;
}


// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease() {
}


//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	gTrg = (gKey ^ keyold) & gKey;
}

// �t���[�������F�v�Z
void FrameProcess() {
	

	//�A�j���[�V�����̏���
	if (GetAnimeMax() != 0) {
		// �A�j���[�V������
		AnimeProcess();
		return;
	}


	//�f�o�b�O�p z�ŃX�e�[�W��i�߂�
	if (gTrg & PAD_INPUT_1)
	{
		stageNo++;
		StageInit(stageNo);
		if (stageNo > STAGE_MAX)
		{
			game = 0;
			stageClear = 0;
			ed = 1;
		}
	}
	//�^�C�g�����
	if (title == 1 && gTrg & PAD_INPUT_10 )
	{
		title = 0;
		op = 1;
	}
	//�I�[�v�j���O�p�[�g
	if (op == 1 && title == 0)
	{
		
		if (gTrg & PAD_INPUT_10)
		{
			wordNum +=1;

			//OP�p�[�g���I�����A�Q�[�����J�n
			if (wordNum > OP_WORDS)
			{
				
				game = 1;
				op = 0;
				wordNum = 0;
				StageInit(stageNo);
			}
		}
		//OP�p�[�g���I�����A�Q�[�����J�n
		if (gTrg & PAD_INPUT_4)//[A]
		{
			op = 0;
			game = 1;
			StageInit(stageNo);
		}
	}
	//�G���f�B���O�p�[�g
	if (ed == 1 && game == 0)
	{
		if (gTrg & PAD_INPUT_10)
		{
			edWordNum += 1;
		}
	}
	//�V�ѕ��̕\��
	if(stageClear == 0 && gKey & PAD_INPUT_7)
	{
		menu = 1;
	}
	else {
		menu = 0;
	}
	


if(game ==1 && menu ==0){
	//������@��\��
	

	if (gameOver == 0)
	{

	// �h�b�g�̏�ɂ��ׂĔ����u���ꂽ���H
	int all_get = 1;		// �S�����ׂ�1�̂܂܂Ȃ�A�S���u�������ƂɂȂ�
	int x, y;
	for (y = 0; y < MAP_H; y++)
	{
		for (x = 0; x < MAP_W; x++)
		{
			// �h�b�g���ǂ������ׂ�
			if (map[y * MAP_W + x] == 2)
			{
				// ��ɔ������邩�H
				if (box[y * MAP_W + x] != 1 )
				{
					// ��������
					all_get = 0;
				}
			}
		}
	}

	// �h�b�g�̏�ɂ��ׂĔ����u����Ă��Ȃ�������A�Q�[���̏���������
	if (all_get == 0 && title == 0)
	{
		// �ړ��O�̏ꏊ������Ă���
		int old_x = playerX;
		int old_y = playerY;

		// �ړ������p�ϐ�
		int move_x = 0;
		int move_y = 0;

		// ���������L�[���������獡�̈ʒu��ۑ�
		if (gTrg & PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_UP + PAD_INPUT_DOWN) {
			SaveOneStep();
		}
		// �L�[���͂𔻒肵�āA��l�����ړ�������
		if (gTrg & PAD_INPUT_LEFT) { playerX--; move_x = -1; arrow = ARROW_LF;}
		if (gTrg & PAD_INPUT_RIGHT) { playerX++; move_x = 1; arrow = ARROW_RI;}
		if (gTrg & PAD_INPUT_UP) { playerY--; move_y = -1; arrow = ARROW_UP;}
		if (gTrg & PAD_INPUT_DOWN) { playerY++; move_y = 1; arrow = ARROW_DN;}
		moveX = move_x;
		moveY = move_y;
		// �v���C���[���ړ������悪�ǂ��H
		if (map[playerY * MAP_W + playerX] >= 10)
		{
			// �ړ������悪�ǂ������̂ŁA�ړ��O�̏ꏊ�ɖ߂�
			playerX = old_x;
			playerY = old_y;
		}

		// �ړ�������ɔ��͂��邩�H
		if (box[playerY * MAP_W + playerX] > 0 )
		{
			// �ړ�������ɔ����������B
			// �����邩�ǂ������ׂ���
			int push_ok = 1;

			// ����ɓ��������̂��̐�̍��W�����߂�i�ړ������p�ϐ��𑫂��j
			int next_x = playerX + move_x;
			int next_y = playerY + move_y;


			// �ړ�������̔��͂ǂꂩ�H
			//�����Ɣ�Ԕ�
			if (box[playerY * MAP_W + playerX] == 1)
			{
				boxType = 1;
			}
			//��}�X������
			else if(box[playerY * MAP_W + playerX] == 2)
			{
				boxType = 2;
			}
			// ���̐�ɁA�ǂ����邩�𒲂ׂ�
			if (map[next_y * MAP_W + next_x] >= 10|| box[next_y * MAP_W + next_x] == 1  || box[next_y * MAP_W + next_x] == 2)		
			{
				// �ǂ�����̂ŉ����Ȃ�
				push_ok = 0;
			}

			// ���ׂ����ʁA������H
			if (push_ok == 1)
			{
				//�������Obox���W
				int box_x;
				int box_y;

				//�����ɂԂ���܂Ői�ޔ�
				if (boxType == 1)
				{
					//�ړ������悪�����S�[���Ȃ�
					if (map[next_y * MAP_W + next_x] == 0 || map[next_y * MAP_W + next_x] == 2)
					{
					
					   //���̈ʒu���ړ�����
						box[playerY * MAP_W + playerX] = 0;
						box[next_y * MAP_W + next_x] = 1;
						
						//������񐔂����炷
						countInstage -= 1;
						
						//�Q�}�X�ڈȍ~�̔��̈ړ�����
						for (int i = 0; i < MAP_W; i++)
						{
							box_x = next_x;
							box_y = next_y;
							next_x += move_x;
							next_y += move_y;

							boxX = box_x;
							boxY = box_y;
							nextX = next_x;
							nextY = next_y;
								

							//���̔�����������i�߂Ȃ�
							if (box[next_y * MAP_W + next_x] == 2)
							{
								SetAnime(box_x, box_y, TRUE);
								break;
							}
							//�����S�[���Ȃ�i�߂�
							if (map[next_y * MAP_W + next_x] == 0 || map[next_y * MAP_W + next_x] == 2)
							{
								SetAnime(next_x, next_y, TRUE);
							}
							//�ǂȂ�i�߂Ȃ�
							if (map[next_y * MAP_W + next_x] >= 10)
							{								
								SetAnime(box_x, box_y, TRUE);
								break;
							}
						}
					}				
				}
				//�P�i�ޔ�
				if (boxType == 2)
				{
					// ���̈ʒu���ړ�����
					box[playerY * MAP_W + playerX] = 0;
					box[next_y * MAP_W + next_x] = 2;
				}			
			}
			//���ׂ����ʁA�����Ȃ�
			else if(push_ok == 0)
			{
				// �����Ȃ��̂ŁA�v���C���[�̈ʒu���ړ��O�̏ꏊ�ɖ߂�
				playerX = old_x;
				playerY = old_y;
			}
			push = push_ok;
		}
		
	}
	// �h�b�g�̏�ɑS���u���Ă���
	if (all_get == 1 && title == 0){	
		
		stageClear = 1;
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// stage[stageNo][] ����A�`�b�v�ԍ������o��
				int chip_no = map[y * MAP_W + x];
				// box[]�̏�������
				if (chip_no == 22) { map[y * MAP_W + x] = 21; }
				if (chip_no == 0) { map[y * MAP_W + x] = 1; }
			}
		}
		
		// ���炵�������玟�̃X�e�[�W��
		if (stageNo + 1 < STAGE_MAX) {
				
			if (gTrg & PAD_INPUT_10)
			{
				stageNo++;
				StageInit(stageNo);
			}
		}
		else if (stageNo + 1 >= STAGE_MAX)
		{
			if (gTrg & PAD_INPUT_10)
			{
				game = 0;
				stageClear = 0;
				ed = 1;
			}
		}
		
	}
	//������񐔂��O�ɂȂ�����Q�[���I�[�o�[
	else if(all_get == 0 && countInstage == 0 && GetAnimeMax() == 0)
	{

		gameOver = 1;
	}
	
	// �X�e�[�W�f�[�^���Z�b�g�i��蒼���j
	if (gTrg & PAD_INPUT_3 && stageClear != 1) {	// [c]
		StageInit(stageNo);
	}

	// �P���߂�
	if (gTrg & PAD_INPUT_2) {	// [x]
		BackOneStep();
	}
	}
	
	animcnt++;	// �A�j���[�V�����J�E���g��i�߂�
  } 
  

  //�Q�[���I�[�o�[��Ԃ�C�L�[����������X�e�[�W���Z�b�g
  if (gTrg & PAD_INPUT_3 && gameOver == 1)// [c]
  {
	  gameOver = 0;
	  StageInit(stageNo);
  }
  
}

// �t���[�������F�`��
void FrameDraw() {

	ClearDrawScreen();						// ��ʂ�����������
	//�^�C�g�����
	if (title == 1) {
		DrawGraph(0, 0, cgTitle, TRUE);
	}
	//�I�[�v�j���O�p�[�g
	if (op == 1 && title == 0 && game == 0 && ed ==0)
	{
		
		if(wordNum == 3 || wordNum == 4)
		{			
			DrawGraph(0, 0, cgBlackBuck, TRUE);
		}
		else if(wordNum != 3 && wordNum != 4)
		{
			DrawGraph(0, 0, opBack, TRUE);
		}
		DrawGraph(400, 200, cgSubCharacter[wordNum], TRUE);
		DrawGraph(1100, 300, cgOpMainCharacter[wordNum], TRUE);
		DrawGraph(-100, -130, cgOpWords[wordNum], TRUE);
		DrawGraph(50, 710, cgOpName[wordNum], TRUE);

		if (wordNum==18)
		{
			DrawGraph(0, 0, howToPlay, TRUE);
		}
		if (wordNum == 19)
		{
			DrawGraph(0, 0, cgManual, TRUE);
		}
		SetFontSize(100);
		//DrawFormatString(0, 300, GetColor(0, 0, 0), "wordNum:%d", wordNum);
		//DrawFormatString(0, 200, GetColor(0, 0, 0), "A�ŃQ�[���p�[�g");

		
	}

	

	//�Q�[���p�[�g
	if (game == 1 && menu == 0 && title == 0 && op == 0 && ed == 0) {

		// �}�b�v�`�b�v�� for ���[�v�łЂƂЂƂ`�悷��
		int x, y;
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// map[] ����A�`�b�v�ԍ������o��
				int chip_no = map[y * MAP_W + x];

				// �`�b�v�ԍ��ɍ��킹���摜���A�}�X�ڂɉ����ĕ`�悷��
				DrawGraph(x * CHIP_W, y * CHIP_H, cgChip[chip_no], FALSE);
			}
		}


		// ����for���[�v�ŕ`�悷��
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// box[] ����A�`�b�v�ԍ������o��
				int chip_no = box[y * MAP_W + x];

				if (chip_no == 1)
				{
					DrawGraph(x * CHIP_W, y * CHIP_H, cgBox[0], TRUE);
				}
				if (chip_no == 2)
				{
					DrawGraph(x * CHIP_W, y * CHIP_H, cgObjectShadow, TRUE);
					DrawGraph(x * CHIP_W, y * CHIP_H, cgObject[(animcnt / objectAnimspeed) % 2], TRUE);
				}
			}
		}




		// �v���C���[�֌W
		DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayerShadow, TRUE);//�e

		int animTbl[] = { 0, 1, 2, 1 };	// �A�j���[�V�������̎w��
		//�v���C���[�̕����ɉ����ăA�j���[�V������ݒ�
		switch (arrow) {
			case ARROW_DN:

				DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayer[arrow * 3 + animTbl[(animcnt / playerAnimspeed) % 4]], TRUE);
				break;
			case ARROW_LF:

				DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayer[arrow * 3 + animTbl[(animcnt / playerAnimspeed) % 4]], TRUE);
				break;
			case ARROW_RI:

				DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayer[arrow * 3 + animTbl[(animcnt / playerAnimspeed) % 4]], TRUE);
				break;
			case ARROW_UP:

				DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayer[arrow * 3 + animTbl[(animcnt / playerAnimspeed) % 4]], TRUE);
				break;
			default:
				DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayer[arrow * 3 + animTbl[(animcnt / playerAnimspeed) % 4]], TRUE);
		}
		
		//������񐔂̕\��
		if(gameOver == 0) {
			DrawGraph(0, 0, cgCountBase, TRUE);
		}
		DrawGraph(64, 64, cgCount[countInstage], TRUE);
		SetFontSize(50);

		// DrawFormatString(0, 300, GetColor(255, 255, 255), "stage%d", stageNo + 1);
		/*
		//�f�o�b�O�p
		DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", countInstage);
		DrawFormatString(0, 150, GetColor(255, 255, 255), "push:%d", push);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "boxX:%d,boxY:%d", boxX, boxY); 
		DrawFormatString(0, 250, GetColor(255, 255, 255), "nextX:%d,nextY:%d", nextX, nextY);
		DrawFormatString(0, 300, GetColor(255, 255, 255), "moveX:%d,moveY:%d", moveX, moveY);
		DrawFormatString(0, 350, GetColor(255, 255, 255), "animcnt:%d", animcnt);
		DrawFormatString(0, 400, GetColor(255, 255, 255), "playerX:%d,playerY:%d", playerX, playerY);
		SetFontSize(20);
		DrawString(0, 1000, "���j���[�F�X�y�[�X�@���߂�FX �X�e�[�W���Z�b�g�FC�@���̃X�e�[�W�FZ", GetColor(255, 255, 255));
		*/
	}

	//���j���[��ʂ̕\��
	if (menu == 1) {
		DrawGraph(0, 0, cgManual, TRUE);
	}
	//�G���f�B���O�p�[�g
	if (ed == 1 && title == 0 && game == 0 && menu == 0)
	{
	
		if (edWordNum >= 5 && edWordNum <= 9)
		{
			DrawGraph(0, 0, cgWhiteBuck, TRUE);
		}
		else if(edWordNum < 5)
		{
			DrawGraph(0, 0, opBack, TRUE);
		}
		DrawGraph(400, 200,  cgEdSubCharacter[edWordNum], TRUE);
		DrawGraph(1100, 300, cgEdMainCharacter[edWordNum], TRUE);
		DrawGraph(-100, -130, cgEdWords[edWordNum], TRUE);
		DrawGraph(50, 710, cgEdName[edWordNum], TRUE);
		SetFontSize(100);
		if (edWordNum > 9)
		{
			DrawGraph(0, 0, cgEnd, TRUE);
		}
	}
	//�Q�[���I�[�o�[
	if (gameOver == 1)
	{	
	    DrawGraph(420, 0, cgGameOver, TRUE);
		DrawGraph(0, 0, cgCountBaseBob, TRUE);
	}

	//�X�e�[�W�N���A
	if (stageClear == 1)
	{
		DrawGraph(400, 0, cgClear, TRUE);
		SetFontSize(50);
		DrawFormatString(750, 600, GetColor(255, 0, 0), "PRESS SPACE KEY");
	}
	
	ScreenFlip();							// ����ʂ̓��e��\��ʂɔ��f������
}


void GameMain()
{
	AppInit();	// ������

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		FrameInput();	// ����
		FrameProcess();	// �v�Z
		FrameDraw();	// �`��
		Update();	//�X�V
		//Draw();		//�`��
		ScreenFlip();
		Wait();		//�ҋ@
	}

	AppRelease();	// ���
}
