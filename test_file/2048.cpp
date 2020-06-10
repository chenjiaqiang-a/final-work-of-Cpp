void MainScene::move_to_left()//左移
{
	int k, tag = 0;//临时数组的变量 ；用于判断棋盘是否有变化 
	for (int i = 0; i < 4; i++)//行开始
	{
		int b[4] = { 0 };//定义一个临时数组来存储相加之后的情况
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[i][j] != 0)//	为0直接跳出if
			{
				int flag = 0;//	用来判断，不为0后面直接复制	
				for (int l = j + 1; l < 4; l++)//找是否有相同的数，l为上一个数	
				{
					if (num[i][l] != 0)//两种情况	
					{
						flag = 1;
						if (num[i][l] == num[i][j])
						{
							b[k++] = 2 * num[i][j];//相同就double
							score++;//得分 
							num[i][j] = num[i][l] = 0;//跳出上一个if	
							break;//跳出if
						}
						else
						{
							b[k++] = num[i][j];//不相同，不相加	
							break;
						}
					}
				}
				if (flag == 0)
					b[k++] = num[i][j];//上一个为0，不需要double，复制给b[]
			}
		}
		b[k] = num[i][3];//最后一个没有检查，复制过去，不管是否为0
		for (int j = 0; j < 4; j++)//检查是否有变化 
		{
			if (num[i][j] != b[j])
			{
				tag = 1;
				break;//跳出 
			}
		}
		for (int j = 0; j < 4; j++)//每一行依次赋复制 
			num[i][j] = b[j];
	}
	if (tag)//是否变化，有则产生新的数字方块 
	{
		update_screen();
		newBrick();
	}
}
