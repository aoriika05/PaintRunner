# include "Game.hpp"

Game::Game(const InitData& init)
	:IScene(init)
{
	getData().Opponent_name = U"";
	// INIファイル
// 全てのセクションを列挙
	for (const auto& section : Game_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Game_BGM")	// Matchingキー
				{
					Game_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}

	area.resize(inl_MazeSize);

	//Print << area.size();
	for (auto i : step(area.size())) {
		area[i.x][i.y].areainfo = getData().maze[i.x][i.y];
		if (getData().maze[i] == 2)
			Goal = i;
	}
	
	getname=0;

	getData().Used1 = { 0,0,0,0,0,0 };
	getData().Used2 = { 0,0,0,0,0,0 };
	getData().ClearTime[0]=0;
	getData().ClearTime[1]=0;
	getData().goal[0]=0;
	getData().goal[1]=0;
	getData().ChangeMaze.resize(300);
	for (auto i : step(300))
	{
		getData().ChangeMaze[i].resize(inl_MazeSize);
	}
	if (net->isMasterClient())
	{
		playernum = 1;
	}
	else
	{
		playernum = 2;
	}
	getData().pnum=playernum;


	if (playernum == 1)
	{
		player.setareapos(1, 1);
		player.oldpos = { 150,150 };
	}
	if (playernum == 2)
	{
		player.setareapos(inl_MazeSize.x - 2, inl_MazeSize.y - 2);
		player.oldpos = { (inl_MazeSize.x - 2) * 100 + 50 ,(inl_MazeSize.y - 2) * 100 + 50 };
	}

	MapSharedSw.start();
	sw.start(); //FPS60
}

void Game::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Game_BGM" + Format(Game_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Game_BGM" + Format(Game_Audio_BGM_num)).play(MixBus0);
	}

	if ((GOALFRAG1 == 1 && GOALFRAG2 == 1) || time.TimeOver())
	{
		AudioAsset(U"Game_BGM" + Format(Game_Audio_BGM_num)).stop();
		//シーン遷移
		getData().ClearMaze.resize(inl_MazeSize);
		for (auto i : step(inl_MazeSize.y))
		{
			for (auto j : step(inl_MazeSize.x))
			{
				getData().ClearMaze[i][j] = area[i][j].areainfo;
			}
		}
		changeScene(State::Result);
	}

	net->update();

	//相手方の通信が切れたらマッチング画面に戻す
	if (!net->isInRoom())
	{
		AudioAsset(U"Game_BGM" + Format(Game_Audio_BGM_num)).stop();
		net->opLeaveRoom();
		changeScene(State::Match);
	}

	if (!net->isMasterClient()&&net->EnemyPlayerName&&isonce)
	{
		//net->opRaiseEvent(2, getData().UserName);
		net->opRaiseEvent(1, static_cast<double>(Time::GetMillisecSinceEpoch()));
		net->StartTiming = Time::GetMillisecSinceEpoch() + 1000;
		isonce = false;
	}

	if(!net->StartTiming||Time::GetMillisecSinceEpoch()<=net->StartTiming||!net->EnemyPlayerName)
	{
		FontAsset(U"Medium_40")(U"相手プレイヤーを待っています").drawAt(Scene::Center());
		return;
	}

	if(getData().Opponent_name==U"")
	{
		getData().Opponent_name = net->EnemyPlayerName.value();
	}

	if(CountDownNum+1>0)
	{
		Mat3x2 mat = Mat3x2::Identity();
		mat = Mat3x2::Scale(2-(fmod(CountDownNum,1.0)), Scene::Center());
		constexpr bool transformCursorPos = false;
		const Transformer2D t(mat, Transformer2D::Target::PushLocal);
		if(CountDownNum+1 <1)
		CountDownFont(U"Start!").drawAt(Scene::Center());
		else
		CountDownFont(static_cast<int>(CountDownNum)+1.0).drawAt(Scene::Center());
		CountDownNum -= Scene::DeltaTime();
		return;
	}

	left = 1; right = 1; top = 1; bottom = 1;
	//player2.pos=もう片方のデータ（player.getpos())を受け取る

	if(getname==0)
	{
		player.name=getData().UserName;
		player2.name=getData().Opponent_name;
		getname=1;
	}
	if (net->LagStopwatch.ms()>Rollbackms)
	{
		/*//敵の前の行動を参考にして、次の行動を予想する
		if (net->enpositons.size() >= 3)
		{
			ActPrediction();
		}*/
	}
	else if (net->enpositons && !net->enpositons[0].isZero())
	{
		player2.pos = net->enpositons[0];
		if (net->enpositons.size() >= 3)
		{
			//敵の位置情報を３つに調整
			net->enpositons.pop_back_N(net->enpositons.size() - 3);
		}
	}

	//GOALFRAG2=もう片方のデータ(GOALFRAG1)を受け取りたい
	GOALFRAG2 = net->EnemyGoalFrag;
	if (GOALFRAG1 == 0)
	{
		player.GearChange(area[player.getpos().x / 100][player.getpos().y / 100].areainfo, playernum);//速度変更
	}
	player.move();//動き
	player.GetDirection();
	//Console << player2.pos;
	//Console << player.pos;
	for (auto i : step(inl_MazeSize.y))
	{
		for (auto j : step(inl_MazeSize.x))
		{
			if (player.collision(area[i][j].wall.left(), area[i][j].areainfo) == 0)//壁の左側に触れたか
			{
				left = 0;
			}
			if (player.collision(area[i][j].wall.right(), area[i][j].areainfo) == 0)//右
			{
				right = 0;
			}
			if (player.collision(area[i][j].wall.top(), area[i][j].areainfo) == 0)//上
			{
				top = 0;
			}
			if (player.collision(area[i][j].wall.bottom(), area[i][j].areainfo) == 0)//下
			{
				bottom = 0;
			}
		}
	}
	if (GOALFRAG1 == 0)
	{
		player.TouchWall(left, right, top, bottom);//壁に触れたら反発する
	}
	for (auto i : step(inl_MazeSize.y))
	{
		for (auto j : step(inl_MazeSize.y))
		{
			area[i][j].draw(i, j, player.pos.x, player.pos.y);//それぞれのマスの描画
		}
	}

	if (GOALFRAG1 == 0 && GOALFRAG2 == 0)
	{
		if (playernum == 1)
		{
			if (player.getareapos() == player2.pos / 100)
			{
				while (1)
				{
					temp1 = Random(0, inl_MazeSize.y-1);
					temp2 = Random(0, inl_MazeSize.x-1);
					if (area[temp1][temp2].areainfo != 1)
					{
						player.setareapos(temp1, temp2);
						break;
					}
				}
				net->opRaiseEvent(2,true);
			}
		}
	}
	if (playernum == 2)
	{
		if (net->EnableWarp == 1)
		{
			while (1)
			{
				temp1 = Random(0, inl_MazeSize.y-1);
				temp2 = Random(0, inl_MazeSize.x-1);
				if (area[temp1][temp2].areainfo != 1)
				{
					player.setareapos(temp1, temp2);
					break;
				}
			}
			net->EnableWarp = 0;
		}
	}
	if (GOALFRAG1 == 0)
	{
		if (player.getareapos() != player.oldpos / 100)
		{
			player.GetRoad(playernum, area[player.oldpos.x / 100][player.oldpos.y / 100].areainfo);
		}
	}
	if (GOALFRAG2 == 0)
	{
		if (player2.pos / 100 != player2.oldpos / 100)
		{
			player2.GetRoad(playernum, area[player2.oldpos.x / 100][player2.oldpos.y / 100].areainfo);
		}
	}
	if (GOALFRAG1 == 0)
	{
		GOALFRAG1 = player.getgoal(area[player.getareapos().x][player.getareapos().y].areainfo);
	}
	if (GOALFRAG1 == 1 && GOALTIME == 0) 
	{
		if(playernum==1)
		{
			getData().ClearTime[0]=time.getEtime();
			getData().goal[0]=1;
			Time1=1;
		}
		else
		{
			getData().ClearTime[1]=time.getEtime();
			getData().goal[1]=1;
			Time1=1;
		}
		log.StringIn(U"あなたがゴールしました");
		log.StringIn(U"残り時間が30秒になります");
		GOALTIME = 1;
		time.GameClearTime();
	}
	if (GOALFRAG1 == 1 && Time1==0) 
	{
		if(playernum==1)
		{
			getData().ClearTime[0]=time.getEtime();
			getData().goal[0]=1;
			Time1=1;
		}
		else
		{
			getData().ClearTime[1]=time.getEtime();
			getData().goal[1]=1;
			Time1=1;
		}
	}
	if (GOALFRAG2 == 1 && GOALTIME == 0)
	{
		if(playernum==2)
		{
			getData().ClearTime[0]=time.getEtime();
			getData().goal[0]=1;
			Time2=1;
		}
		else
		{
			getData().ClearTime[1]=time.getEtime();
			getData().goal[1]=1;
			Time2=1;
		}
		log.StringIn(U"相手がゴールしました");
		log.StringIn(U"残り時間が30秒になります");
		GOALTIME = 1;
		time.GameClearTime();
	}
	if (GOALFRAG2 == 1 && Time2==0)
	{
		if(playernum==2)
		{
			getData().ClearTime[0]=time.getEtime();
			getData().goal[0]=1;
			Time2=1;
		}
		else
		{
			getData().ClearTime[1]=time.getEtime();
			getData().goal[1]=1;
			Time2 = 1;
		}
	}
	//琢磨

	//アイテム入手
	if (!GI.items.isEmpty()) {
		for (auto i : step(GI.items.size())) {
			if (GI.items[i].Obtain(player.getareapos())) {

				for (auto j : step(4)) {
					if (j < 3) {
						if (GI.own_items[j].info == -1) {
							GI.own_items[j] = GI.items[i];
							break;
						}
					}
					else {
						GI.own_items<< GI.items[i];
					}

				}

				GI.items.remove_at(i);
				break;
			}
			GI.items[i].draw(player.pos);
		}
	}



	//if(Used==True){
	//
	//}
	//



	if (!GI.own_items.isEmpty()) {
		for (int i = 0; i < 3; i++) {
			if (GI.own_items.size() > i) {
				switch (GI.own_items[i].info) {
				case 0:

					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {
						GI.used_items << 0;

						if (playernum == 1) {
							getData().Used1[0]++;
						}
						else {
							getData().Used2[0]++;
						}

						player.basespeed += 2;
						GI.own_items[i].Situation = 2;
					}

					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 3) {
						player.basespeed -= 2;
					}

					break;

				case 1:

					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {
						GI.used_items << 1;

						if (playernum == 1) {
							getData().Used1[1]++;

						}
						else {
							getData().Used2[1]++;
						}

						//相手にアイテムを使ったことを知らせる
						//SpeedDownUsed();
						net->opRaiseEvent(100, 1 + 10 * i);

						GI.own_items[i].Situation = 2;
					}

					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 3) {

						net->opRaiseEvent(100, 2 + 10 * i);

						//相手にアイテムの使用時間が終わったことを知らせる

					}

					break;

				case 2:
					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {
						GI.used_items << 2;

						if (playernum == 1) {
							getData().Used1[2]++;

						}
						else {
							getData().Used2[2]++;

						}

						vision = GI.own_items[i].vision_scale_up;
						GI.own_items[i].Situation = 2;
					}

					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 3) {
						vision = vision_default;
					}


					break;

				case 3:
					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {
						GI.used_items << 3;

						if (playernum == 1) {
							getData().Used1[3]++;
						}
						else {
							getData().Used2[3]++;
						}

						//相手にアイテムを使ったことを知らせる
						net->opRaiseEvent(200, 1 + 10 * i);
						GI.own_items[i].Situation = 2;
					}



					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 3) {
						//相手にアイテムの使用時間が終わったことを知らせる
						net->opRaiseEvent(200, 2 + 10 * i);
					}


					break;

				case 4:
					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {

						if (playernum == 1) {
							getData().Used1[4]++;
						}
						else {
							getData().Used2[4]++;
						}

						// 相手の座標を変数に格納
						GI.own_items[i].Situation = 2;
					}

					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 2) GI.own_items[i].draw_dirToPl2(player.pos, player2.pos);
					break;

				case 5:
					if (Input(InputDeviceType::Keyboard, 0x31 + i).down() && GI.own_items[i].Situation == 1) {
						GI.used_items << 5;

						if (playernum == 1) {
							getData().Used1[5]++;
						}
						else {
							getData().Used2[5]++;
						}

						GI.own_items[i].Situation = 2;
					}

					GI.own_items[i].Time();

					if (GI.own_items[i].Situation == 2) GI.own_items[i].draw_dirToGoal(player.pos, Goal);
					break;
				default:
					break;
				}
			}
		}
	}

	if (playernum == 1) {
		net->opRaiseEvent(11, getData().Used1);
		getData().Used2 = net->UsedItem2;
	}

	if (playernum == 2) {
		net->opRaiseEvent(12, getData().Used2);
		getData().Used1 = net->UsedItem1;
	} 

	for (auto i : step(3)) {

		if (net->SpeedDown == i*10+1 && ItemUsed[i]== 0) {
			player.basespeed -= 2;
			log.StringIn(U"遅くなるアイテムが使われました");
			ItemUsed[i] = 1;
		}

		if (net->SpeedDown == i * 10 + 2 && ItemUsed[i] == 1) {
			log.StringIn(U"元の速度に戻りました");
			player.basespeed += 2;
			ItemUsed[i] = 0;
		}
		if (net->VisionDown== i * 10 + 1 && ItemUsed[i] == 0) {
			log.StringIn(U"視野が狭くなるアイテムが使われました");
			vision = voidItem.vision_scale_down;
			ItemUsed[i] = 1;
		}
		if (net->VisionDown== i * 10 + 2 && ItemUsed[i] == 1) {
			log.StringIn(U"元の視野に戻りました");
			vision = vision_default;
			ItemUsed[i] = 0;
		}

	}

	//琢磨
	player2.GetDirection();
	player.draw(playernum);//描画
	
	for (auto i : step(inl_MazeSize))
	{
		getData().ChangeMaze[time.getEtime()][i.y][i.x] = area[i.y][i.x].areainfo;
	}

	if (GOALFRAG2 == 0)
	{
		player2.draw(player.pos, playernum);
	}
	//player.getpos()を渡したい
	net->opRaiseEventCustomType(1, player.getpos());
	//GOALFRAG1を渡したい
	if (GOALFRAG1)
	{
		net->opRaiseEvent(1, GOALFRAG1);
	}

	time.update();//時間の減少
	vision.drawAt(Scene::Center());//視界の描画

	//琢磨
	if (!GI.own_items.isEmpty()) {

		for (auto i : step(3)) {
			if (GI.own_items[i].Situation == 3) {
				if (GI.own_items.size() > 3) {
					GI.own_items[i] = GI.own_items[3];
					GI.own_items.remove_at(3);
				}
				else {
					GI.own_items[i] = Item(-1);
				}
				
			}
		}
	}

	GI.draw_inventory();
	//琢磨
	time.draw();//時間の描画
	player.oldpos = player.getpos();
	player2.oldpos = player2.pos;
	Rect(597, 3, 200, 200).drawFrame(0, 3);
	for (auto i : step(inl_MazeSize.x))
	{
		for (auto j : step(inl_MazeSize.y))
		{
			if (playernum == 1)
			{
				if (area[i][j].areainfo == 3)
				{
					RectF((double)(597) + (double)(200) / (double)(inl_MazeSize.x) * (double)(i), (double)(3) + (double)(200) / (double)(inl_MazeSize.y) * (double)(j), (double)(200) / (double)(inl_MazeSize.x), (double)(200) / (double)(inl_MazeSize.y)).draw(Palette::Blue);
				}
			}
			if (playernum == 2)
			{
				if (area[i][j].areainfo == 4)
				{
					RectF((double)(597) + (double)(200) / (double)(inl_MazeSize.x) * (double)(i), (double)(3) + (double)(200) / (double)(inl_MazeSize.y) * (double)(j), (double)(200) / (double)(inl_MazeSize.x), (double)(200) / (double)(inl_MazeSize.y)).draw(Palette::Red);
				}
			}
		}
	}
	Circle(597 + 100 / (double)(inl_MazeSize.x) + 200 /(double)(inl_MazeSize.x) * player.getareapos().x, 3 + 100 / (double)(inl_MazeSize.x) + 200 / (double)(inl_MazeSize.x) * player.getareapos().y, 100 / (double)(inl_MazeSize.x)).draw(Palette::White);
	if(MapSharedSw.s()>3)
	{
		m_PaintArea.resize(area.size());
		for(const auto& index:Iota2D(area.size()))
		{
			m_PaintArea[index] = (area[index].areainfo== ((playernum - 1) ? 4 : 3));
		}
		RLE rle;
		net->opRaiseEvent(55, rle.make(m_PaintArea, area.size().y, area.size().x));
		MapSharedSw.restart();
	}

	if(net->EnemyMapState)
	{
		//Console << net->EnemyMapState;
		for(const auto& index:Iota2D(area.size()))
		{
			if(area[index].areainfo==0&& net->EnemyMapState.value()[index]==1)
			{
				area[index].areainfo = ((playernum - 1) ? 3 : 4);
			}
		}
		net->EnemyMapState = none;
		//Console.writeln();
	}
	
	while (sw.msF() < 1000.0 / FPS);    //1/60秒経過するまでループ
	sw.restart();   //FPS60  ストップウォッチをリスタート
	log.update();
}






