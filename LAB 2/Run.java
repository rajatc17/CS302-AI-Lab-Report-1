public class Run{
	
	static int end[][]= { // 2 = not available, 1 = occupied, 0 = empty
			{2,2,0,0,0,2,2},
			{2,2,0,0,0,2,2},
			{0,0,0,0,0,0,0},
			{0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0},
			{2,2,0,0,0,2,2},
			{2,2,0,0,0,2,2}
	};
	static int p[][]= { // 2 = not available, 1 = occupied, 0 = empty
			{2,2,1,1,1,2,2},
			{2,2,1,1,1,2,2},
			{1,1,1,1,1,1,1},
			{1,1,1,0,1,1,1},
			{1,1,1,1,1,1,1},
			{2,2,1,1,1,2,2},
			{2,2,1,1,1,2,2}
	};
	
	
public static void main(String [] args){
	DFS sol = new DFS(end,p);
}
}