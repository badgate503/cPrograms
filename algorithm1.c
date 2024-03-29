#include <stdio.h>
#define MAT_SIZE 4      //Size of the given matrix.

int matrix[MAT_SIZE][MAT_SIZE]={{ 0, -2, -7,  0},
                                { 9,  2, -6,  2},
                                {-4,  1, -4,  1},    //test matrix.
                                {-1,  8,  0, -2}};
                            
int getMinMatrixAlgo1();                   /*The first algorithm to calculate the minimum submatrix sum
                                             simply by traversing all kinds of possibilities */
int getMinMatrixAlgo2();                   /*The second algorithm to calculate the minimum submatrix sum*/       

int getSubVectorSum(int RowCol, int top, int left, int length);   /*Function that calculates the sum of a specific
                                                                   submatrix given by TopLeft Position and Size */
int getSubMatrixSum(int top, int left, int width, int height);   /*Function that calculates the sum of a specific
                                                                   submatrix given by TopLeft Position and Size */
int main()
{
    
    printf("The MAXIMUM SUBMATRIX SUM is: %d", getMinMatrixAlgo2());
    return 0;
}



int getSubMatrixSum(int top, int left, int width, int height)   //Implementation of getSubmatrix()
{
    int i, j, res = 0;
    for(i = 0; i < width; i++)          //Traverses the columns.
    {
        for(j = 0; j < height; j++)     //Traverses the rows.
        {
            res += matrix[top+j][left+i];
        }
    }
    return res > 0 ? res : 0;
}

int getMinMatrixAlgo1()                       
{
    int w, h, t, l;     //Loop variable short for width, height, top, left, respectively. 
    int max = 0, tmpRes;
    for(w = 1; w <= MAT_SIZE; w++)            //Traverses all possibilites of widths
    {
        for(h = 1; h <= MAT_SIZE; h++)        //Traverses all possibilites of heights
        {
            for(l = 0; l < MAT_SIZE - w + 1; l++)          //Traverses all possibilites of left positions, avoids overbounding
            {
                for(t = 0; t < MAT_SIZE - h + 1; t++)      //Traverses all possibilites of top positions, avoids overbounding
                {
                    tmpRes = getSubMatrixSum(t, l, w, h);
                    //printf("%d %d ; %d %d : %d\n", t, l, w, h, tmpRes);    //Test logs
                    if(max < tmpRes) max = tmpRes;
                }
            }
        }
    }
    return max;
}

int getSubVectorSum(int RowCol, int top, int left, int length)
{
    int i, res = 0;
    for(i = 0; i < length; i++)
    {
        res += matrix[top][left + i];
    }
    return res;
}

int getMinMatrixAlgo2()
{
    int i, j, k, w, l, thisSum, max;
    max = 0;
    for(l = 0; l < MAT_SIZE; l++)
    {
        for(w = 1; w <= MAT_SIZE - l; w++)
        {
            thisSum = 0;
            for(k = 0; k < MAT_SIZE; k++)
            {
                thisSum += getSubVectorSum(1, k, l, w);
                if(thisSum > max)
                {
                    max = thisSum;
                }
                else if(thisSum < 0)
                {
                    thisSum = 0;
                }
            }
        }
    }
    return max;

}