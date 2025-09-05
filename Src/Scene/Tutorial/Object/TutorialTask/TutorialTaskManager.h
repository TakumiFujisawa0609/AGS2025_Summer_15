#pragma once

#include<string>

#include"Task1/Task1.h"
#include"Task3/Task3.h"
#include"Task4/Task4.h"


class TutorialTaskManager
{
public:
	enum class TASK
	{
		START,
		TASK1,
		TASK2,
		TASK3,
		TASK4,
		TASK5,

		MAX
	};

	TutorialTaskManager();
	~TutorialTaskManager();

	void Load(void);
	void Init(void);
	bool Update(void);
	void Draw(void);
	void DrawUI(void);
	void Release(void);

	const TASK& GetNowTask(void)const { return nowTask_; }
	const bool& GetTaskConp(void)const { return taskConp_; }

	TaskBase* GetTask(void) { return taskIns_[(int)nowTask_]; }

private:
	TASK nowTask_;

	bool NextTask(void);

	TaskBase* taskIns_[(int)TASK::MAX];

	const std::wstring START_LINES_TABLE[(int)TASK::MAX] =
	{
		L"",
		L"まずは基本の剣術からじゃ\nXボタンまたはRトリガーで発動できる通常攻撃じゃ\n試しにその竹を切り倒してみろ",
		L"だがこの基本の剣撃はこんなものではないぞ\nあらゆるものを「相殺」「反射」することができるのだ\n試しにわしの攻撃を「相殺」しろみろ",
		L"次はBAMBOO奥義「竹投げ」じゃ\n竹を持って、通常攻撃と同じボタンで発動できる必殺技じゃ\n攻撃ボタンを長押しすることで正確に狙いを定めることができる\n試しに上の３つの的をなるべく動かず打ちぬいてみろ",
		L"もう一つ教えておこう。\n気づいているかもしれないが\nあらゆるものを「反射」する剣撃は\nもちろん自分で投げた竹も対象だ。実践してみろ",
		L"最後に回避も教えておく\nBボタンまたはLトリガーで発動する、文字通り「回避」じゃ\n敵の攻撃をやり過ごすことができる\n試しにわしの攻撃を避けてみろ"
	};

	const std::wstring END_LINES_TABLE[(int)TASK::MAX] =
	{
		L"ビシバシ行くから覚悟せいよ",
		L"これが基本の剣撃、「通常攻撃」だ",
		L"うむ、なかなか筋がいいな",
		L"なかなか早いじゃないか\nこの「竹投げ」は回数制限付きで反射する性質を持っておる\nさらに反射するほど威力が増すという特徴もある\nうまく使って大ダメージを狙うといい",
		L"いい太刀筋だ\n弾くことで竹の反射回数の制限をリセットすることができる\nもちろん威力はそのままでな\n積極的にやっていくといい",
		L"良くやった、教えられることはもうない\nこれで強敵とも渡り合えるじゃろう\nさあ、あの化け物たちを倒しに行ってこい！！"
	};

	int hukidashiImg_;
	int nextButtonImg_[2];
	int nextButtonCounter_;

	std::string nowLines_;
	int linesCount_;
	static constexpr int LINES_INTERVAL = 5;
	int linesInterval_;

	bool taskConp_;
};
