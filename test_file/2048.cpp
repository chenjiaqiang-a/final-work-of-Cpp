void MainScene::move_to_left()//����
{
	int k, tag = 0;//��ʱ����ı��� �������ж������Ƿ��б仯 
	for (int i = 0; i < 4; i++)//�п�ʼ
	{
		int b[4] = { 0 };//����һ����ʱ�������洢���֮������
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[i][j] != 0)//	Ϊ0ֱ������if
			{
				int flag = 0;//	�����жϣ���Ϊ0����ֱ�Ӹ���	
				for (int l = j + 1; l < 4; l++)//���Ƿ�����ͬ������lΪ��һ����	
				{
					if (num[i][l] != 0)//�������	
					{
						flag = 1;
						if (num[i][l] == num[i][j])
						{
							b[k++] = 2 * num[i][j];//��ͬ��double
							score++;//�÷� 
							num[i][j] = num[i][l] = 0;//������һ��if	
							break;//����if
						}
						else
						{
							b[k++] = num[i][j];//����ͬ�������	
							break;
						}
					}
				}
				if (flag == 0)
					b[k++] = num[i][j];//��һ��Ϊ0������Ҫdouble�����Ƹ�b[]
			}
		}
		b[k] = num[i][3];//���һ��û�м�飬���ƹ�ȥ�������Ƿ�Ϊ0
		for (int j = 0; j < 4; j++)//����Ƿ��б仯 
		{
			if (num[i][j] != b[j])
			{
				tag = 1;
				break;//���� 
			}
		}
		for (int j = 0; j < 4; j++)//ÿһ�����θ����� 
			num[i][j] = b[j];
	}
	if (tag)//�Ƿ�仯����������µ����ַ��� 
	{
		update_screen();
		newBrick();
	}
}
