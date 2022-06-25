int board[6][6]={
	{14,3,7,13,15,15},
	{15,9,2,1,3,12},
	{6,8,2,7,5,7},
	{11,6,1,0,12,9},
	{15,9,6,1,7,5},
	{14,8,11,14,1,12}
};
int length;
int adj[36][4]={0};

int* give_adj(int i, int j)
{
	int config=board[i][j];
	int cell=6*i+j+1;
	int *ret=(int *)malloc(sizeof(int)*4);
	switch(config)
	{
		case 0 : ret[0]=cell+1;ret[1]=cell-1;ret[2]=cell+6;ret[3]=cell-6;break;
		case 1 : ret[0]=cell+1;ret[1]=cell-1;ret[2]=cell-6;ret[3]=0;break;
		case 2 : ret[0]=cell+1;ret[1]=cell+6;ret[2]=cell-6;ret[3]=0;break;
		case 3 : ret[0]=cell+1;ret[1]=cell-1;ret[2]=cell+6;ret[3]=0;break;
		case 4 : ret[0]=cell-1;ret[1]=cell-6;ret[2]=cell+6;ret[3]=0;break;
		case 5 : ret[0]=cell+1;ret[1]=cell-6;ret[2]=0;ret[3]=0;break;
		case 6 : ret[0]=cell+1;ret[1]=cell+6;ret[2]=0;ret[3]=0;break;
		case 7 : ret[0]=cell-1;ret[1]=cell+6;ret[2]=0;ret[3]=0;break;
		case 8 : ret[0]=cell-1;ret[1]=cell-6;ret[2]=0;ret[3]=0;break;
		case 9 : ret[0]=cell+6;ret[1]=cell-6;ret[2]=0;ret[3]=0;break;
		case 10: ret[0]=cell+1;ret[1]=cell-1;ret[2]=0;ret[3]=0;break;
    case 11: ret[0]=cell-6;ret[1]=0;ret[2]=0;ret[3]=0;break;
    case 12: ret[0]=cell-1;ret[1]=0;ret[2]=0;ret[3]=0;break;
 		case 13: ret[0]=cell+6;ret[1]=0;ret[2]=0;ret[3]=0;break; 
 		case 14: ret[0]=cell+1;ret[1]=0;ret[2]=0;ret[3]=0;break;
    case 15: ret[0]=0;ret[1]=0;ret[2]=0;ret[3]=0;break;


	}
	return ret;
}

void update_adj()
{
	for(int i=0;i<6;i++)
	{
		for (int j=0;j<6;j++)
		{
			int *temp;
			temp=give_adj(i,j);
			adj[6*i+j][0]=temp[0];
			adj[6*i+j][1]=temp[1];
			adj[6*i+j][2]=temp[2];
			adj[6*i+j][3]=temp[3];
		}
	}
}

int * dfs()
{
	bool visited[36];
	for(int i=0;i<36;i++)
		visited[i]=0;
	int dist[6][6];
	for(int i=0;i<6;i++)
		for (int j=0;j<6;j++)
			dist[i][j]=99;
	dist[0][0]=0;
	while(visited[35]==0)
	{
		int min=INT8_MAX,cell=1;

		for(int i=0;i<6;i++) //to find the cell which has the minimum distace in the array "dist"
		{
			for (int j=0;j<6;j++)
			{
				if (min>dist[i][j] && visited[i*6+j]==0)
					{
						min=dist[i][j];
						cell=6*i+j+1;
					}
			}
		}
		visited[cell-1]=1;
		for(int i=0;i<4;i++)
		{	
			int newcell=adj[cell-1][i];
			if (visited[newcell-1]==1)
				continue;
			if (newcell==0)
				break;
			dist[(newcell-1)/6][(newcell-1)%6]=dist[(cell-1)/6][(cell-1)%6]+1;
		}
	}
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			Serial.print(dist[i][j]);
			Serial.print("  ");
		}
		Serial.println();
	}

	int cell,d=INT8_MAX;
	for (int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			if (d>dist[i+2][j+2])
				{
					d=dist[i+2][j+2];
					cell=(i+2)*6+j+3;
				}
		}
	}
	int * path,index=0;
	length=d+1;
	path=(int *)malloc(sizeof(int)*d+1);
	path[0]=cell;
	while(d>=0)
	{
		d=d-1;
		for (int i=0;i<4;i++)
		{
			int adjac=adj[path[index]-1][i];
			if (adjac==0)
				break;
			if (d==dist[(adjac-1)/6][(adjac-1)%6])
			{
				path[index+1]=adjac;
				break;
			}
		}
		index++;
	}
	
	return path;

}



void setup() {
  Serial.begin(9600);
  update_adj();
  
  int path[36];
  int * temp=dfs();

  for(int i=length-1;i>=0;i--)
  {
  	path[length-i-1]=temp[i];
  }
  for(int i=0;i<length;i++)
  	Serial.println(path[i]);

}

void loop() {
}