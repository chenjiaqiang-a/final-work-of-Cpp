void MainScene::PressDown(){                  //下移的情况	
    int k, tag = 0;	
    for (int i = 0; i < 4; i++){           //从每一列开始		
	    int b[4] = { 0 };				 //定义一个临时数组来存储相加之后的情况		
	    k = 3;		
		for (int j = 3; j > 0; j--){		
		    if (a[j][i] != 0){			
		        int flag = 0;				
		        for (int l = j - 1; l >= 0; l--){    //找是否有相同的数						
			        if (a[l][i] != 0){						
				        flag = 1;					
					    if (a[l][i] == a[j][i]){				
							b[k--] = 2 * a[j][i];						
							num++;         							
							a[l][i] = a[j][i] = 0;							
							break;					
							}					
						else{
							b[k--] = a[j][i];						
							break;					
						}				
					}		
			    }			
				if (flag == 0)b[k--] = a[j][i];			
			}	
		}	
		b[k] = a[0][i];                 //最后一个没有检查，赋值过去，不管是否为0，都无所谓的		
		for (int j = 0; j < 4; j++){     //检查是否有移动				
			if (a[j][i] != b[j]){				
				tag = 1;				
				break;			
			}		
		}	
		for (int j = 0; j < 4; j++)a[j][i] = b[j];	
	}	
	if (tag) creat_num();                         //存在移动，产生新的数		
	}

void MainScene::pressLeft(){                 //同上
    int k, tag = 0;	
	for (int i = 0; i < 4; i++){		
	    int b[4] = { 0 };		
		k = 0;		
		for (int j = 0; j < 3; j++){			
		    if (a[i][j] != 0){				
			    int flag = 0;				
				for (int l = j + 1; l < 4; l++){					
					if (a[i][l] != 0){						
					    flag = 1;						
						if (a[i][l] == a[i][j]){							
						    b[k++] = 2 * a[i][j];							
							num++;							
							a[i][j] = a[i][l] = 0;						
							break;					
						}						
						else{							
						    b[k++] = a[i][j];						
							break;						
						}					
					}				
				}				
				if (flag == 0)b[k++] = a[i][j];
			}		
		}		
		b[k] = a[i][3];		
		for (int j = 0; j < 4; j++){			
		    if (a[i][j] != b[j]){				
			    tag = 1;				
				break;			
			}		
		}		
		for (int j = 0; j < 4; j++)	a[i][j] = b[j];	
	}	
	if (tag)creat_num();
}

void MainScene::pressRight(){              //同上
	int k, tag = 0;	
    for (int i = 0; i < 4; i++){		
        int b[4] = { 0 };		
        k = 3;	
	    for (int j = 3; j > 0; j--){			
		    if (a[i][j] != 0){		
			    int flag = 0;				
				for (int l = j - 1; l >= 0; l--){					
					if (a[i][l] != 0){					
						flag = 1;					
						if (a[i][l] == a[i][j]){						
							b[k--] = 2 * a[i][j];					
							num++;						
							a[i][j] = a[i][l] = 0;						
							break;					
						}			
						else{						
							b[k--] = a[i][j];							
							break;					
						}				
					}			
				}			
			    if (flag == 0)b[k--] = a[i][j];			
			}	
		}	
		b[k] = a[i][0];	
		for (int j = 0; j < 4; j++){		
			if (a[i][j] != b[j]){		
				tag = 1;	
				break;	
		    }	
		}		
	    for (int j = 0; j < 4; j++)a[i][j] = b[j];	
	}	
	if (tag)creat_num();
}

void MainScene::pressUp(){	
    int k, tag = 0;	for (int i = 0; i < 4; i++)	{		
        int b[4] = { 0 };                 //定义一个临时数组来存储相加之后的情况		
        k = 0;		
        for (int j = 0; j < 3; j++){			
            if (a[j][i] != 0){				
	            int flag = 0;			
		        for (int l = j + 1; l < 4; l++){    //找是否有相同的数				
					if (a[l][i] != 0){				
					    flag = 1;						
		                if (a[l][i] == a[j][i]){							
		                    b[k++] = 2 * a[j][i];							
		                    num++;							
		                    a[l][i] = a[j][i] = 0;						
		                	break;					
				        }					
					    else{						
							b[k++] = a[j][i];						
							break;					
						} 
					}				
				}				
				if (flag == 0)b[k++] = a[j][i];		
			}	
		}		
	        b[k] = a[3][i];	
			for (int j = 0; j < 4; j++){	
				if (a[j][i] != b[j]){			
					tag = 1;				
					break;			
				}	
			}	
			for (int j = 0; j < 4; j++)a[j][i] = b[j];      //将结果覆盖回去		
	}
	if (tag)creat_num();
}

