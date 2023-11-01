#include <iostream>

using namespace std;

char matrix[4][4] = { {'0', '0', '0', '0'}, {'0', '1', '2', '3'}, {'0', '4', '5', '6'}, {'0', '7', '8', '9'} };
char mark = 'x';
int turn = 0;

// Khởi tạo phiên chơi mới
void initNewGame()
{
    char tmp[4][4] = { {'0', '0', '0', '0'}, {'0', '1', '2', '3'}, {'0', '4', '5', '6'}, {'0', '7', '8', '9'} };
    memcpy((void*)matrix, (void*)tmp, sizeof(tmp));
    mark = 'x';
    turn = 0;
}

// Hiện thị lên màn hình 
void display(string res)
{
    system("cls");
    cout << "           TIC TAC TOE" << endl;

    cout << "Player 1 (x) - Player 2 (o) " << endl << endl << endl;

    for (int i = 1; i <= 3; i++) {
        printf("       |       |       |\n");
        printf("   %c   |   %c   |   %c   |\n", matrix[i][1], matrix[i][2], matrix[i][3]);
        if (i == 3) {
            printf("       |       |       |\n");
            break;
        }
        printf("_______|_______|_______|\n");
    }

    // The match still continues
    if (res == "continue")
        cout << endl << "Player " << turn + 1 << ", please enter a number: ";

    // Announced victory!
    else if (res == "win")
        cout << endl << "Congratulations player " << (turn == 0 ? 2 : 1) << "!";

    // Announced draw!
    else if (res == "draw")
        cout << endl << "Draw!";
}

// Thực hiện đánh vào ô pos
bool makeMove(short pos)
{
    if (pos % 3 != 0) {
        if (matrix[pos / 3 + 1][pos % 3] < '9') {
            matrix[pos / 3 + 1][pos % 3] = mark;
            return true;
        }
    }
    else if (matrix[pos / 3][3] <= '9') {
        matrix[pos / 3][3] = mark;
        return true;
    }
    return false;
}

// Thực hiện kiểm tra hàng thứ row
short checkRow(int row)
{
    char mark = min(min(matrix[row][1], matrix[row][2]), matrix[row][3]);

    if (matrix[row][1] == matrix[row][2] && matrix[row][2] == matrix[row][3]) {
        return mark == 'x' ? 1 : 2;
    }

    if (mark < 'o') {
        return 0;
    }

    return -1;
}

// Thực hiện kiểm tra cột thứ col
short checkCol(int col)
{
    char mark = min(min(matrix[1][col], matrix[2][col]), matrix[3][col]);

    if (matrix[1][col] == matrix[2][col] && matrix[2][col] == matrix[3][col]) {
        return mark == 'x' ? 1 : 2;
    }
    if (mark < 'o') {
        return 0;
    }

    return -1;

}

// Thực hiện kiểm tra đường chéo thứ nhất
short checkFirstDiagonalLine()
{
    char mark = min(min(matrix[1][1], matrix[2][2]), matrix[3][3]);

    if (matrix[1][1] == matrix[2][2] && matrix[2][2] == matrix[3][3]) {
        return mark == 'x' ? 1 : 2;
    }
    if (mark < 'o') {
        return 0;
    }
    return -1;
}

// Thực hiện kiểm tra đường chéo thứ hai
short checkSecondDiagonalLine()
{
    char mark = min(min(matrix[1][3], matrix[2][2]), matrix[3][1]);

    if (matrix[1][3] == matrix[2][2] && matrix[2][2] == matrix[3][1]) {
        return mark == 'x' ? 1 : 2;
    }
    if (mark < 'o') {
        return 0;
    }
    return -1;
}

// Thực hiện kiểm tra kết quả ván đấu
short checkForWin()
{
    short res = max(checkFirstDiagonalLine(), checkSecondDiagonalLine());

    for (int i = 1; i <= 3; i++) {

        if (res == 1 || res == 2)
            return res;

        res = max(res, checkCol(i));

        if (res == 1 || res == 2)
            return res;

        res = max(res, checkRow(i));
    }

    return res;
}

// Bắt đầu màn chơi
void startPVP()
{
    char isAgain = 0;
    short pos = -1;

    do {
        initNewGame();

        do {
            display("continue");

            cin >> pos;

            while (!makeMove(pos)) {
                display("continue");
                cout << "Invalid move! Please enter again: ";
                cin >> pos;
            }

            turn = (turn + 1) % 2;
            mark = turn == 0 ? 'x' : 'o';
        } while (checkForWin() == 0);

        if (checkForWin() == -1) {
            display("draw");
        }
        else
            display("win");

        cout << endl << "Play again? (press 1 to agree): ";
        cin >> isAgain;

    } while (isAgain == '1');
}

int main()
{
    startPVP();

    return 0;
}
