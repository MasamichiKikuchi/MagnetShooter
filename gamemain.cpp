#include	"DxLib.h"
#include <math.h>
//
// 定数・構造体定義
//

// チップのサイズ
#define	CHIP_W		(64)
#define	CHIP_H		(64)

// マップのサイズ
#define	MAP_W		(30)
#define	MAP_H		(17)

#define STAGE_MAX (3)
// 箱のアニメーションのフレーム数
#define	ANIME_FRAME	(5)

// 4方向定義
#define	ARROW_DN	(0)	// 下
#define	ARROW_LF	(1)	// 左
#define	ARROW_RI	(2)	// 右
#define	ARROW_UP	(3)	// 上

#define	OP_WORDS	(19) //オープニングパートのセリフ数
#define	ED_WORDS	(10) //エンディングパートのセリフ数

// 箱の位置を示す構造体
struct POSITION
{
	int	x;
	int y;
};

//
// グローバル変数宣言
//

// マップデータ
int	map[MAP_W * MAP_H]; 
int box[MAP_W * MAP_H];

// アニメーション用のボード
int gAnimeBoard[MAP_W * MAP_H];	

// ステージデータ(mapとboxとplayer位置を混ぜたもの)
// 0:壁, 1:player, 2:押すと飛ぶ箱, 3:１マス動く箱,4:ゴール地点, 6～9:床,10以上：壁
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

// 手の保存データ（マップ＋プレイヤー位置）
int stepsave_map[MAP_W * MAP_H];
int stepsave_box[MAP_W * MAP_H];
int stepsave_playerX;
int stepsave_playerY;
int countSave;

//箱を押せる回数
int countInstage;



// 画像データ
int cgChip[99];		// チップ画像（配列）
int cgPlayer[3 * 4];		// プレイヤー
int cgBox[2];		// 箱(移動オブジェクト）
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
int howToPlay;//遊び方

int cgPlayerShadow;
int cgObjectShadow;
int cgObject[2];	

int cgEnd;


// ゲーム情報
int gKey;			// キー入力の情報
int gTrg;			// トリガ入力の情報

// プレイヤー情報
int playerX, playerY;	// 座標（チップ単位）
int	arrow;		// 向いている方向
int boxType;

//シーン遷移
int title; //タイトルのフラグ
int menu; //メニュー画面のフラグ
int gameOver; //ゲームオーバーのフラグ
int stageClear; //クリア演出のフラグ
int op; //クリア演出のフラグ
int game; //ゲーム画面のフラグ
int ed; //エンディングのフラグ

//ステージの番号
int stageNo;

// アニメーション関連
int gAnimeCnt;			// アニメーションのカウント
int animcnt;	// アニメーションカウンタ
int playerAnimspeed = 10;
int objectAnimspeed = 20;
//アドベンチャーパート関連
int wordNum;
int edWordNum;
//デバッグ用
int boxX;
int boxY;
int push;
int nextX;
int nextY;
int moveX;
int moveY;
int goalX;
int goalY;

static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;	//設定したFPS


void StageInit(int stageNo) {

	stageClear = 0;
	//ステージ情報の初期化
	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			
			box[y * MAP_W + x] = 0;					
			map[y * MAP_W + x] = 0;				
		}
	}


	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// stage[stageNo][] から、チップ番号を取り出す
			// 0以下:壁, 1:player, 2:押すと飛ぶ箱, 3:１マス動く箱,4:ゴール地点, 6以上:床
			int chip_no = stage[stageNo][y * MAP_W + x];
			// box[]の書き込み
			box[y * MAP_W + x] = 0;
			if (chip_no == 2) { box[y * MAP_W + x] = 1; }
			if (chip_no == 3) { box[y * MAP_W + x] = 2; }
			// map[]の書き込み
			map[y * MAP_W + x] = 0;
			if (chip_no == 6) { map[y * MAP_W + x] = 0; }   // 床
			if (chip_no == 0) { map[y * MAP_W + x] = 1; }   // 壁
			if (chip_no == 4) { map[y * MAP_W + x] = 2; }	// ゴール地点
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
				// ここにプレイヤー座標を設定
				map[y * MAP_W + x] = 0;
				playerX = x;
				playerY = y;
			}
		}
	}
	countInstage = count[stageNo];
}

// 1手保存する関数
void SaveOneStep() {
	// stepsave に、現状を保存
	for (int n = 0; n < MAP_W * MAP_H; n++) {
		stepsave_map[n] = map[n];
		stepsave_box[n] = box[n];
	}
	stepsave_playerX = playerX;
	stepsave_playerY = playerY;
	countSave = countInstage;
}

// 1手戻す関数
void BackOneStep() {
	// stepsave を、現状にコピー
	for (int n = 0; n < MAP_W * MAP_H; n++) {
		map[n] = stepsave_map[n];
		box[n] = stepsave_box[n];
	}
	playerX = stepsave_playerX;
	playerY = stepsave_playerY;
	countInstage = countSave;
}

//オブジェクトの位置を取得
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

//飛ぶBOXをセット
void SetBox(int x, int y, int state)
{
	box[y * MAP_W + x] = state;
}

// アニメーションの最大番号を取得
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

// 箱のアニメーションをセットする
// 引数:
//   x = 箱のX
//   y = 箱のY
//   set = 0:アニメーション無し, 1:アニメーションの順番をセット
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


//アニメーションの場所を取得
POSITION GetAnimePos()
{
	POSITION pos = { -1, -1 };
	int number = GetAnimeMax();

	// アニメーションは無い
	if (number == 0) {
		return pos;
	}

	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			int n = gAnimeBoard[y * MAP_W + x];
			// 1番番号が小さい場所を取得
			if (n != 0 && n <= number) {
				number = n;
				pos.x = x;
				pos.y = y;
			}
		}
	}
	return pos;
}

// アニメーション処理
void AnimeProcess()
{
	gAnimeCnt++;
	// ANIME_FRAME毎に 1 コマだけ処理していく
	if (gAnimeCnt >= ANIME_FRAME) {
		gAnimeCnt = 0;

		// アニメーションするコマを取得
		POSITION pos = GetAnimePos();

		if (pos.x >= 0 && pos.y >= 0)
		{
			POSITION nowpos = GetBoxPos();	
			
			// 箱をセットしてアニメーションを消す
			SetBox(nowpos.x, nowpos.y, 0);
			SetAnime(nowpos.x, nowpos.y, FALSE);
			SetBox(pos.x, pos.y, 1);			
			SetAnime(pos.x, pos.y, FALSE);
		}
	}
}

bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
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
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

// アプリの初期化
// 起動時に1回だけ実行される
void AppInit() {
	// 画像の読み込み
	//マップ関係
	cgChip[0] = LoadGraph("res/床光.png");
	cgChip[1] = LoadGraph("res/床改 完成.png");
	cgChip[2] = LoadGraph("res/ゴール （仮）調整済み.png");
	cgChip[3] = LoadGraph("res/dot.png");
	cgChip[10] = LoadGraph("res/壁パターン1.png");
	cgChip[11] = LoadGraph("res/壁パターン2 .png");
	cgChip[12] = LoadGraph("res/壁パターン3 .png");
	cgChip[13] = LoadGraph("res/壁パターン4 .png");
	cgChip[14] = LoadGraph("res/壁右 .png");
	cgChip[15] = LoadGraph("res/壁右上 .png");
	cgChip[16] = LoadGraph("res/壁下 .png");
	cgChip[17] = LoadGraph("res/壁左 .png");
	cgChip[18] = LoadGraph("res/壁左上 .png");
	cgChip[19] = LoadGraph("res/壁上 .png");
	cgChip[20] = LoadGraph("res/壁側面normal.png");
	cgChip[21] = LoadGraph("res/壁側面電気あり.png");
	cgChip[22] = LoadGraph("res/壁側面電気なし.png");
	cgChip[23] = LoadGraph("res/宇宙パターン1.png");
	cgChip[24] = LoadGraph("res/宇宙パターン2.png");
	cgChip[25] = LoadGraph("res/宇宙パターン3.png");
	cgChip[26] = LoadGraph("res/紫ブロック.png");
	
	//キャラクター、オブジェクト
	LoadDivGraph("res/スライド1.画像切り抜きtouka.png", 3 * 4, 3, 4, 64, 64, cgPlayer);
	LoadDivGraph("res/robot1.png", 2, 2, 1, 64, 64, cgObject);
	cgPlayerShadow = LoadGraph("res/影.png");
	cgObjectShadow = LoadGraph("res/影touka.png");
	cgBox[0] = LoadGraph("res/bloc.png");
	cgBox[1] = LoadGraph("res/robo (1).png");
	
	//押せる回数
	cgCountBase = LoadGraph("res/惑星.png");
	cgCountBaseBob = LoadGraph("res/惑星爆発300.png");
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
	//各演出の画像
	cgClear = LoadGraph("res/CLEAR.png");
	cgGameOver = LoadGraph("res/GAME OVER.png");
	cgEnd = LoadGraph("res/おしまい.png");
	howToPlay = LoadGraph("res/プレゼンテーション3.png");
	cgTitle = LoadGraph("res/title.png");
	cgManual = LoadGraph("res/そうさほうほう.png");

	//オープニング関連
	//主人公の画像[0]はつくらない
	cgOpMainCharacter[1] = LoadGraph("");
	cgOpMainCharacter[2] = LoadGraph("");
	cgOpMainCharacter[3] = LoadGraph("");
	cgOpMainCharacter[4] = LoadGraph("");
	cgOpMainCharacter[5] = LoadGraph("res/ネット君(驚き).png");
	cgOpMainCharacter[6] = LoadGraph("res/ネット君(驚き).png");
	cgOpMainCharacter[7] = LoadGraph("res/ネット君(笑顔).png");
	cgOpMainCharacter[8] = LoadGraph("res/ネット君(笑顔).png");
	cgOpMainCharacter[9] = LoadGraph("res/ネット君(疑問).png");
	cgOpMainCharacter[10] = LoadGraph("res/ネット君(疑問).png");
	cgOpMainCharacter[11] = LoadGraph("res/ネット君(不機嫌).png");
	cgOpMainCharacter[12] = LoadGraph("res/ネット君(不機嫌).png");
	cgOpMainCharacter[13] = LoadGraph("res/ネット君(驚き).png");
	cgOpMainCharacter[14] = LoadGraph("res/ネット君(驚き).png");
	cgOpMainCharacter[15] = LoadGraph("res/デフォルメネット君(驚き).png");
	cgOpMainCharacter[16] = LoadGraph("res/デフォルメネット君(驚き).png");
	cgOpMainCharacter[17] = LoadGraph("res/デフォルメネット君(笑顔).png");

	//サブキャラクターの画像[0]はつくらない
	cgSubCharacter[1] = LoadGraph("");
	cgSubCharacter[2] = LoadGraph("");
	cgSubCharacter[3] = LoadGraph("");
	cgSubCharacter[4] = LoadGraph("");
	cgSubCharacter[5] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[6] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[7] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[8] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[9] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[10] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[11] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[12] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[13] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[14] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[15] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[16] = LoadGraph("res/博士立ち絵touka.png");
	cgSubCharacter[17] = LoadGraph("res/博士立ち絵touka.png");
	//セリフ画像　[0]はつくらない
	cgOpWords[1] = LoadGraph("");
	cgOpWords[2] = LoadGraph("res/スライド2.PNG");//ドカーン
	cgOpWords[3] = LoadGraph("res/スライド2.toukapng.png");
	cgOpWords[4] = LoadGraph("res/スライド3 kirinuki.PNG");
	cgOpWords[5] = LoadGraph("res/スライド4 kirinuki.PNG");
	cgOpWords[6] = LoadGraph("res/スライド5 kirinuki.PNG");
	cgOpWords[7] = LoadGraph("res/スライド6 kirinuki.PNG");
	cgOpWords[8] = LoadGraph("res/スライド7 kirinuki.PNG");
	cgOpWords[9] = LoadGraph("res/スライド8 kirinuki.png");
	cgOpWords[10] = LoadGraph("res/スライド9 kirinuki.PNG");
	cgOpWords[11] = LoadGraph("res/スライド10 kirinuki.PNG");
	cgOpWords[12] = LoadGraph("res/スライド11 kirinuki.PNG");
	cgOpWords[13] = LoadGraph("res/スライド12 kirinuki.PNG");
	cgOpWords[14] = LoadGraph("res/スライド13 kirinuki.PNG");
	cgOpWords[15] = LoadGraph("res/スライド13 kirinuki.PNG");
	cgOpWords[16] = LoadGraph("res/スライド14 kirinuki.PNG");
	cgOpWords[17] = LoadGraph("res/スライド15 kirinuki.PNG");

	//キャラクター名表示　[0]はつくらない
	cgOpName[1] = LoadGraph("");
	cgOpName[2] = LoadGraph("");
	cgOpName[3] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[4] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[5] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[6] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[7] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[8] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[9] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[10] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[11] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[12] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[13] = LoadGraph("");
	cgOpName[14] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[15] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgOpName[16] = LoadGraph("res/博士　名前　背景透過.png");
	cgOpName[17] = LoadGraph("res/ネットくん　名前　背景透過.png");
	//背景
	opBack = LoadGraph("res/utyuusen haikei kannsei 1.jpg");
	//セリフ番号
	wordNum = 0;

	//エンディング関連
	//主人公の画像
	cgEdMainCharacter[0] = LoadGraph("res/ネット君(笑顔).png");
	cgEdMainCharacter[1] = LoadGraph("res/ネット君(笑顔).png");
	cgEdMainCharacter[2] = LoadGraph("res/ネット君(驚き).png");
	cgEdMainCharacter[3] = LoadGraph("res/ネット君(疑問).png");
	cgEdMainCharacter[4] = LoadGraph("res/ネット君(驚き).png");
	cgEdMainCharacter[5] = LoadGraph("");
	cgEdMainCharacter[6] = LoadGraph("");
	cgEdMainCharacter[7] = LoadGraph("");
	cgEdMainCharacter[8] = LoadGraph("");
	cgEdMainCharacter[9] = LoadGraph("");

	//サブキャラクターの画像
	cgEdSubCharacter[0] = LoadGraph("res/博士枠.png");
	cgEdSubCharacter[1] = LoadGraph("res/博士枠.png");
	cgEdSubCharacter[2] = LoadGraph("res/博士枠.png");
	cgEdSubCharacter[3] = LoadGraph("res/博士枠.png");
	cgEdSubCharacter[4] = LoadGraph("res/博士枠.png");
	cgEdSubCharacter[5] = LoadGraph("");
	cgEdSubCharacter[6] = LoadGraph("");
	cgEdSubCharacter[7] = LoadGraph("");
	cgEdSubCharacter[8] = LoadGraph("");
	cgEdSubCharacter[9] = LoadGraph("");
	//セリフ画像
	cgEdWords[0] = LoadGraph("res/スライド16 kirinuki.PNG");
	cgEdWords[1] = LoadGraph("res/スライド17 kirinuki.PNG");
	cgEdWords[2] = LoadGraph("res/スライド18 kirinuki.PNG");
	cgEdWords[3] = LoadGraph("res/スライド19 kirinuki.PNG");
	cgEdWords[4] = LoadGraph("res/スライド20 kirinuki.PNG");
	cgEdWords[5] = LoadGraph("");
	cgEdWords[6] = LoadGraph("res/スライド21 kirinuki.PNG");
	cgEdWords[7] = LoadGraph("res/スライド22 kirinuki.PNG");
	cgEdWords[8] = LoadGraph("res/スライド23 kirinuki.PNG");
	cgEdWords[9] = LoadGraph("res/スライド24 kirinuki.PNG");


	//キャラクター名表示　
	cgEdName[0] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgEdName[1] = LoadGraph("res/博士　名前　背景透過.png");
	cgEdName[2] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgEdName[3] = LoadGraph("res/博士　名前　背景透過.png");
	cgEdName[4] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgEdName[5] = LoadGraph("");
	cgEdName[6] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgEdName[7] = LoadGraph("res/ネットくん　名前　背景透過.png");
	cgEdName[8] = LoadGraph("res/博士　名前　背景透過.png");
	cgEdName[9] = LoadGraph("res/ネットくん　名前　背景透過.png");

	//背景
	cgEdBack = LoadGraph("res/背景　宇宙船内２.jpg");
	cgBlackBuck = LoadGraph("res/blak.png");
	cgWhiteBuck = LoadGraph("res/white.png");
	
	//セリフ番号
	edWordNum = 0;

	// プレイヤー情報の初期化
	playerX = 2;
	playerY = 2;

	//シーン遷移フラグ
	title = 1;
	menu = 0;
	gameOver = 0;

	//ステージ番号
	stageNo = 0;
	
	//キャラクターのアニメーション速度
	gAnimeCnt = 0;
}


// アプリの解放
// 終了時に1回だけ実行される
void AppRelease() {
}


//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput() {
	// キーの入力、トリガ入力を得る
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	gTrg = (gKey ^ keyold) & gKey;
}

// フレーム処理：計算
void FrameProcess() {
	

	//アニメーションの処理
	if (GetAnimeMax() != 0) {
		// アニメーション中
		AnimeProcess();
		return;
	}


	//デバッグ用 zでステージを進める
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
	//タイトル画面
	if (title == 1 && gTrg & PAD_INPUT_10 )
	{
		title = 0;
		op = 1;
	}
	//オープニングパート
	if (op == 1 && title == 0)
	{
		
		if (gTrg & PAD_INPUT_10)
		{
			wordNum +=1;

			//OPパートを終了し、ゲームを開始
			if (wordNum > OP_WORDS)
			{
				
				game = 1;
				op = 0;
				wordNum = 0;
				StageInit(stageNo);
			}
		}
		//OPパートを終了し、ゲームを開始
		if (gTrg & PAD_INPUT_4)//[A]
		{
			op = 0;
			game = 1;
			StageInit(stageNo);
		}
	}
	//エンディングパート
	if (ed == 1 && game == 0)
	{
		if (gTrg & PAD_INPUT_10)
		{
			edWordNum += 1;
		}
	}
	//遊び方の表示
	if(stageClear == 0 && gKey & PAD_INPUT_7)
	{
		menu = 1;
	}
	else {
		menu = 0;
	}
	


if(game ==1 && menu ==0){
	//操作方法を表示
	

	if (gameOver == 0)
	{

	// ドットの上にすべて箱が置かれたか？
	int all_get = 1;		// 全部調べて1のままなら、全部置いたことになる
	int x, y;
	for (y = 0; y < MAP_H; y++)
	{
		for (x = 0; x < MAP_W; x++)
		{
			// ドットかどうか調べる
			if (map[y * MAP_W + x] == 2)
			{
				// 上に箱があるか？
				if (box[y * MAP_W + x] != 1 )
				{
					// 箱が無い
					all_get = 0;
				}
			}
		}
	}

	// ドットの上にすべて箱が置かれていなかったら、ゲームの処理をする
	if (all_get == 0 && title == 0)
	{
		// 移動前の場所を取っておく
		int old_x = playerX;
		int old_y = playerY;

		// 移動方向用変数
		int move_x = 0;
		int move_y = 0;

		// 何か方向キーを押したら今の位置を保存
		if (gTrg & PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_UP + PAD_INPUT_DOWN) {
			SaveOneStep();
		}
		// キー入力を判定して、主人公を移動させる
		if (gTrg & PAD_INPUT_LEFT) { playerX--; move_x = -1; arrow = ARROW_LF;}
		if (gTrg & PAD_INPUT_RIGHT) { playerX++; move_x = 1; arrow = ARROW_RI;}
		if (gTrg & PAD_INPUT_UP) { playerY--; move_y = -1; arrow = ARROW_UP;}
		if (gTrg & PAD_INPUT_DOWN) { playerY++; move_y = 1; arrow = ARROW_DN;}
		moveX = move_x;
		moveY = move_y;
		// プレイヤーが移動した先が壁か？
		if (map[playerY * MAP_W + playerX] >= 10)
		{
			// 移動した先が壁だったので、移動前の場所に戻す
			playerX = old_x;
			playerY = old_y;
		}

		// 移動した先に箱はあるか？
		if (box[playerY * MAP_W + playerX] > 0 )
		{
			// 移動した先に箱があった。
			// 押せるかどうか調べたい
			int push_ok = 1;

			// さらに同じ方向のその先の座標を求める（移動方向用変数を足す）
			int next_x = playerX + move_x;
			int next_y = playerY + move_y;


			// 移動した先の箱はどれか？
			//押すと飛ぶ箱
			if (box[playerY * MAP_W + playerX] == 1)
			{
				boxType = 1;
			}
			//一マス動く箱
			else if(box[playerY * MAP_W + playerX] == 2)
			{
				boxType = 2;
			}
			// その先に、壁があるかを調べる
			if (map[next_y * MAP_W + next_x] >= 10|| box[next_y * MAP_W + next_x] == 1  || box[next_y * MAP_W + next_x] == 2)		
			{
				// 壁があるので押せない
				push_ok = 0;
			}

			// 調べた結果、押せる？
			if (push_ok == 1)
			{
				//動かす前box座標
				int box_x;
				int box_y;

				//何かにぶつかるまで進む箱
				if (boxType == 1)
				{
					//移動した先が床かゴールなら
					if (map[next_y * MAP_W + next_x] == 0 || map[next_y * MAP_W + next_x] == 2)
					{
					
					   //箱の位置を移動する
						box[playerY * MAP_W + playerX] = 0;
						box[next_y * MAP_W + next_x] = 1;
						
						//押せる回数を減らす
						countInstage -= 1;
						
						//２マス目以降の箱の移動処理
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
								

							//他の箱があったら進めない
							if (box[next_y * MAP_W + next_x] == 2)
							{
								SetAnime(box_x, box_y, TRUE);
								break;
							}
							//床かゴールなら進める
							if (map[next_y * MAP_W + next_x] == 0 || map[next_y * MAP_W + next_x] == 2)
							{
								SetAnime(next_x, next_y, TRUE);
							}
							//壁なら進めない
							if (map[next_y * MAP_W + next_x] >= 10)
							{								
								SetAnime(box_x, box_y, TRUE);
								break;
							}
						}
					}				
				}
				//１つ進む箱
				if (boxType == 2)
				{
					// 箱の位置を移動する
					box[playerY * MAP_W + playerX] = 0;
					box[next_y * MAP_W + next_x] = 2;
				}			
			}
			//調べた結果、押せない
			else if(push_ok == 0)
			{
				// 押せないので、プレイヤーの位置を移動前の場所に戻す
				playerX = old_x;
				playerY = old_y;
			}
			push = push_ok;
		}
		
	}
	// ドットの上に全部置けていた
	if (all_get == 1 && title == 0){	
		
		stageClear = 1;
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// stage[stageNo][] から、チップ番号を取り出す
				int chip_no = map[y * MAP_W + x];
				// box[]の書き込み
				if (chip_no == 22) { map[y * MAP_W + x] = 21; }
				if (chip_no == 0) { map[y * MAP_W + x] = 1; }
			}
		}
		
		// 減らしきったら次のステージへ
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
	//押せる回数が０になったらゲームオーバー
	else if(all_get == 0 && countInstage == 0 && GetAnimeMax() == 0)
	{

		gameOver = 1;
	}
	
	// ステージデータリセット（やり直し）
	if (gTrg & PAD_INPUT_3 && stageClear != 1) {	// [c]
		StageInit(stageNo);
	}

	// １歩戻す
	if (gTrg & PAD_INPUT_2) {	// [x]
		BackOneStep();
	}
	}
	
	animcnt++;	// アニメーションカウントを進める
  } 
  

  //ゲームオーバー状態でCキーを押したらステージリセット
  if (gTrg & PAD_INPUT_3 && gameOver == 1)// [c]
  {
	  gameOver = 0;
	  StageInit(stageNo);
  }
  
}

// フレーム処理：描画
void FrameDraw() {

	ClearDrawScreen();						// 画面を初期化する
	//タイトル画面
	if (title == 1) {
		DrawGraph(0, 0, cgTitle, TRUE);
	}
	//オープニングパート
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
		//DrawFormatString(0, 200, GetColor(0, 0, 0), "Aでゲームパート");

		
	}

	

	//ゲームパート
	if (game == 1 && menu == 0 && title == 0 && op == 0 && ed == 0) {

		// マップチップを for ループでひとつひとつ描画する
		int x, y;
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// map[] から、チップ番号を取り出す
				int chip_no = map[y * MAP_W + x];

				// チップ番号に合わせた画像を、マス目に沿って描画する
				DrawGraph(x * CHIP_W, y * CHIP_H, cgChip[chip_no], FALSE);
			}
		}


		// 箱もforループで描画する
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				// box[] から、チップ番号を取り出す
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




		// プレイヤー関係
		DrawGraph(playerX * CHIP_W, playerY * CHIP_H, cgPlayerShadow, TRUE);//影

		int animTbl[] = { 0, 1, 2, 1 };	// アニメーション順の指定
		//プレイヤーの方向に応じてアニメーションを設定
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
		
		//押せる回数の表示
		if(gameOver == 0) {
			DrawGraph(0, 0, cgCountBase, TRUE);
		}
		DrawGraph(64, 64, cgCount[countInstage], TRUE);
		SetFontSize(50);

		// DrawFormatString(0, 300, GetColor(255, 255, 255), "stage%d", stageNo + 1);
		/*
		//デバッグ用
		DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", countInstage);
		DrawFormatString(0, 150, GetColor(255, 255, 255), "push:%d", push);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "boxX:%d,boxY:%d", boxX, boxY); 
		DrawFormatString(0, 250, GetColor(255, 255, 255), "nextX:%d,nextY:%d", nextX, nextY);
		DrawFormatString(0, 300, GetColor(255, 255, 255), "moveX:%d,moveY:%d", moveX, moveY);
		DrawFormatString(0, 350, GetColor(255, 255, 255), "animcnt:%d", animcnt);
		DrawFormatString(0, 400, GetColor(255, 255, 255), "playerX:%d,playerY:%d", playerX, playerY);
		SetFontSize(20);
		DrawString(0, 1000, "メニュー：スペース　一手戻る：X ステージリセット：C　次のステージ：Z", GetColor(255, 255, 255));
		*/
	}

	//メニュー画面の表示
	if (menu == 1) {
		DrawGraph(0, 0, cgManual, TRUE);
	}
	//エンディングパート
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
	//ゲームオーバー
	if (gameOver == 1)
	{	
	    DrawGraph(420, 0, cgGameOver, TRUE);
		DrawGraph(0, 0, cgCountBaseBob, TRUE);
	}

	//ステージクリア
	if (stageClear == 1)
	{
		DrawGraph(400, 0, cgClear, TRUE);
		SetFontSize(50);
		DrawFormatString(750, 600, GetColor(255, 0, 0), "PRESS SPACE KEY");
	}
	
	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}


void GameMain()
{
	AppInit();	// 初期化

	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		FrameInput();	// 入力
		FrameProcess();	// 計算
		FrameDraw();	// 描画
		Update();	//更新
		//Draw();		//描画
		ScreenFlip();
		Wait();		//待機
	}

	AppRelease();	// 解放
}
