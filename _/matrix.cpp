#include "../common.h"
#include "SimMatrix.h"

int main() {
    /*自定义简易矩阵类*/
    /*//case1 基本功能：矩阵的四则运算、转置、单位矩阵、求和、点积（内积）
    double p[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    SimMatrix<double> m1(3, 4, p), m2(3, 4, p), m3, e(4);
    m3 = m1.transposition() * (m2 + 10) * e;
    e.show(3);
    cout << m3 << m3.sum(); NHR;*/

    /*//case2 矩阵的点积、张量积
    int p1[] = {1,2, 3,1}, p2[] = {0,3, 2,1};
    SimMatrix<int> m1(2, 2, p1), m2(2, 2, p2), m3, m4;
    m3 = m1.hadamard(m2);  //点积
    cout << m3;
    m4 = m1.kronecker(m2);  //张量积
    cout << m4;*/

    /*//case3 单通道矩阵的卷积计算：N = (W + 2P - F) / S + 1
    int p[] = {2,2,2,0,2, 1,0,1,0,0, 2,1,0,0,0, 2,1,0,2,1, 0,2,1,1,2}, f[] = {0,1,-1, -1,-1,1, 1,1,-1};
    SimMatrix<int> m1(5, 5, p), m2(3, 3, f), m3;
    m3 = m1.convolution(m2, 1, 2);
    cout << m3;*/

    /*CNN卷积层计算*/
    //数据准备
    const int input_edge = 5, filter_edge = 3, channels = 3, depth = 2, stride = 1, zero_padding = 1;
    const double input[input_edge][input_edge][channels] = {
        {{0, 1, 2}, {1, 1, 0}, {1, 1, 2}, {2, 2, 0}, {2, 0, 2}},
        {{0, 0, 0}, {1, 2, 0}, {1, 1, 1}, {0, 1, 2}, {0, 2, 1}},
        {{1, 1, 1}, {1, 2, 0}, {0, 0, 2}, {1, 0, 2}, {0, 2, 1}},
        {{1, 0, 2}, {0, 2, 0}, {1, 1, 2}, {1, 2, 0}, {1, 1, 0}},
        {{0, 2, 0}, {2, 0, 0}, {0, 1, 1}, {1, 2, 1}, {0, 0, 2}}
    }, filter[depth][filter_edge][filter_edge][channels] = {
        {
            {{1, -1, 0}, {1, 0, 1}, {-1, -1, 0}},
            {{-1, 0, 1}, {0, 0, 0}, {1, -1, 1}},
            {{-1, 1, 0}, {-1, -1, -1}, {0, 0, 1}}
        }, {
            {{-1, 1, -1}, {-1, -1, 0}, {0, 0, 1}},
            {{-1, -1, 1}, {1, 0, 0}, {0, -1, 1}},
            {{-1, -1, 0}, {1, 0, -1}, {0, 0, 0}}
        }
    }, bias[depth] = {1, 0};
    //初始化输出矩阵
    int output_edge = (input_edge + 2 * zero_padding - filter_edge) / stride + 1;
    double output[output_edge][output_edge][depth];
    for (int i = 0, j, k; i < output_edge; ++i)
        for (j = 0; j < output_edge; ++j) for (k = 0; k < depth; ++k) output[i][j][k] = 0;
    //包裹输入矩阵
    const int edge = input_edge + 2 * zero_padding;
    double _input[edge][edge][channels];
    for (int i = 0; i < edge; ++i) {
        for (int j = 0; j < edge; ++j)
            for (int k = 0; k < channels; ++k)
                if(i < zero_padding || edge - i <= zero_padding)
                    _input[i][j][k] = 0;
                else if(j < zero_padding || edge - j <= zero_padding)
                    _input[i][j][k] = 0;
                else
                    _input[i][j][k] = input[i - zero_padding][j - zero_padding][k];
    }
    //卷积计算
    int end = edge - filter_edge + 1, deep, ch, oi, oj, row, col, i_, j_;
    double sum;
    for (deep = 0; deep < depth; ++deep) {  //卷积层循环
        for (ch = 0; ch < channels; ++ch)  //通道循环
            for (row = oi = oj = 0; row < end; row += stride)  //输入层行列循环
                for (col = 0; col < end; col += stride) {
                    for (i_ = 0, sum = 0; i_ < filter_edge; ++i_)  //卷积核行列循环
                        for (j_ = 0; j_ < filter_edge; ++j_)
                            sum += _input[row + i_][col + j_][ch] * filter[deep][i_][j_][ch];
                    output[oi][oj++][deep] += sum;  //卷积核求和
                    if(oj == output_edge) ++oi, oj = 0;
                }
        for(row = 0; row < output_edge; ++row)  //添加偏置项
            for(col = 0; col < output_edge; ++col) output[row][col][deep] += bias[deep];
    }
    //输出矩阵展示
    for (int k = 0; k < depth; ++k) {
        for (int i = 0; i < output_edge; ++i) {
            for (int j = 0; j < output_edge; ++j) cout << setw(3) << output[i][j][k];
            cout << endl;
        }
        HR;
    }

    return 0;
}