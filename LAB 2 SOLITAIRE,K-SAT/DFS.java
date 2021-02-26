import java.util.Arrays;
import java.util.LinkedList;

public class DFS {
	int end[][];
	int p[][];
	boolean scan = false;
	int count;
	LinkedList<int[][]> board = new LinkedList<int[][]>();
	LinkedList<Integer> finalMov = new LinkedList<Integer>();
	
	int global_i = 0;
	int global_j = 0;
	int global_function = 0;
	
public DFS(int[][] end, int[][] ){
	this.end = end;
	this. = p;
	printBoard(p);
	long start = System.currentTimeMillis();
	do{
		getAvaiable(global_i,global_j,global_function);
	}while(scan == false);
	long end = (System.currentTimeMillis() - start) / 1000;
	System.out.println("It took "+end+" second to run with total of "+count+" iteration.");
}

public void getAvaiable(int last_i, int last_j, int functionUsed){
	int i = 0;
	int j = 0;
	int functionNumber = 0;
	boolean localCheck = false;
	if(scan == false){
		outer:
		for(i = last_i; i < p.length; i++){
	    	for(j = last_j; j < p[i].length; j++){
	    		if((p[i][j]) == 1){
	    			if(i+2 < p.length && p[i+2][j]==0 && functionUsed <= 1){
	    				if(p[i+1][j] == 1){
	    					board.add(saveBoardToLinkedList(p));
	    					p[i][j] = 0;
	    					p[i+1][j] = 0;
	    					p[i+2][j] = 1;
	    					localCheck = true;
	    					functionNumber = 1;
	    					break outer;
	    				}
	    			}
	    			if((i-2 >= 0 && p[i-2][j]==0) && functionUsed <= 2){
	    				if(p[i-1][j] == 1){
	    					board.add(saveBoardToLinkedList(p));
	    					p[i][j] = 0;
	    					p[i-1][j] = 0;
	    					p[i-2][j] = 1;
	    					localCheck = true;
	    					functionNumber = 2;
	    					break outer;
	    				}
	    			}
	    			if(j+2 < p.length && p[i][j+2] ==0 && functionUsed <= 3){
	    				if(p[i][j+1] == 1){
	    					board.add(saveBoardToLinkedList(p));
	    					p[i][j] = 0;
	    					p[i][j+1] = 0;
	    					p[i][j+2] = 1;
	    					localCheck = true;
	    					functionNumber = 3;
	    					break outer;
	    				}
	    			}
	    			if((j-2 >= 0 && p[i][j-2]==0) && functionUsed <= 4){
	    				if(p[i][j-1]==1){
	    					board.add(saveBoardToLinkedList(p));
	    					p[i][j] = 0;
	    					p[i][j-1] = 0;
	    					p[i][j-2] = 1;
	    					localCheck = true;
	    					functionNumber = 4;
	    					break outer;
	    				}
	    			}
	    		}
	    		functionUsed = 0;
	    		last_j = 0;
	    	}
	    }
		if(localCheck == true){
			checkGoal(p);
			finalMov.add(count);
			finalMov.add(functionNumber);
			finalMov.add(j);
			finalMov.add(i);
			count++;
			global_i = 0;
			global_j = 0;
			global_function = 0;
		}else{
			p = board.pollLast();
			global_i = finalMov.pollLast();
			global_j = finalMov.pollLast();
			global_function = finalMov.pollLast() + 1;
			int localCount = finalMov.pollLast();
		}
	}
}

public int[][] saveBoardToLinkedList(int[][] p){
	int[][] result = new int[p.length][p.length];
	for(int i = 0; i < p.length; i++){
		for(int j = 0; j < p[i].length; j++){
			result[i][j] = p[i][j];
		}
	}
return result;
}
public void checkGoal(int[][] p){
	if(Arrays.deepEquals(end, p)){
		scan = true;
		System.out.println("Solution Found");
		printBoard(p);
	}
}
public void printBoard(int[][] p){
	for(int i = 0; i < p.length;i++){
		for(int j = 0; j < p[i].length; j++){
			if(p[i][j] == 2)
				System.out.print("  ");
			else if(p[i][j] == 1)
				System.out.print("1 ");
			else if(p[i][j] == 0)
				System.out.print("0 ");
		}
		System.out.println("");
	}
}
}