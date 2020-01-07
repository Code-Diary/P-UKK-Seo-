#include <cstring>
#include <queue>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

enum cell_status {
  NONE,
  DISABLED,
  ACTIVE,
  REPRODUCING,
  ALIVE,
  DEAD
};

class Cell {
  public :
    static int cur_time;
    static enum cell_status status[751][751];
    static int birth_time[751][751];
    static int period[751][751];
    static int cnt;
    int x, y;

    Cell (int p_period, int p_x, int p_y) {
      x = p_x;
      y = p_y;
      set_birth_time();
      set_period(p_period);
      set_status(DISABLED);
    }

    Cell (int p_x, int p_y) {
      x = p_x;
      y = p_y;
    }

    static int get_cnt() {
      return cnt;
    }

    static void next_time() {
      cur_time++;
    }

    int get_period() {
      int X = 350 + x;
      int Y = 350 + y;
      return period[X][Y];
    }

    void set_period(int p_period) {
      int X = 350 + x;
      int Y = 350 + y;
      if (get_birth_time() == cur_time && get_period() < p_period)
        period[X][Y] = p_period;
    }

    int get_birth_time() {
      int X = 350 + x;
      int Y = 350 + y;
      return birth_time[X][Y];
    }

    void set_birth_time() {
      int X = 350 + x;
      int Y = 350 + y;
      if (get_birth_time() == 0) {
        birth_time[X][Y] = cur_time;
        cnt++;
      }
    }

    static int count_cells () {
      int  count = 0;
      for (int i = 0; i < 751; i++)
        for (int j = 0; j < 751; j++) {
          if (!(status[i][j] == NONE|| status[i][j] == DEAD))
            count++;
        }
      return count;
    }

    int get_status() {
      int X = 350 + x;
      int Y = 350 + y;
      return status[X][Y];
    }

    static int check_status(int x, int y) {
      int X = 350 + x;
      int Y = 350 + y;
      return status[X][Y];
    }

    void set_status(enum cell_status new_status) {
      int X = 350 + x;
      int Y = 350 + y;
      status[X][Y] = new_status;
    }

    void kill() {
      set_status(DEAD);
      cnt--;
    }

    void reproduce () {
      int running_time = cur_time - get_birth_time();
      if (get_status() == DISABLED && running_time == get_period()) {
        set_status(ACTIVE);
      } else if (get_status() == ACTIVE && running_time == get_period()+1) {
        set_status(REPRODUCING);
      } else if (get_status() == ALIVE && running_time >= get_period()*2) {
        kill();
      }
    }
};

int Cell::cur_time;
enum cell_status Cell::status[751][751];
int Cell::birth_time[751][751];
int Cell::period[751][751];
int Cell::cnt;



int n, m, k;
list<Cell> q;


void solve (int testcase) {
  q.clear();
  Cell::cur_time = 0;
  memset(Cell::status, 0, sizeof(enum cell_status)*751*751);
  memset(Cell::birth_time, 0, sizeof(int)*751*751);
  memset(Cell::period, 0, sizeof(int)*751*751);
  Cell::cnt = 0;
  cin >> n >> m >> k;
  for (int i = 0;  i < n; i++) {
    for (int j = 0;  j < m; j++) {
      int period;
      scanf("%d", &period);
      if (period != 0)
        q.push_back(Cell(period, i, j));
    }
  }

  vector<Cell> new_cells;
  for (int time = 1; time <= k; time++) {
    new_cells.clear();
    Cell::next_time();
    for (list<Cell>::iterator it = q.begin(); it != q.end(); ) {
      it->reproduce();
      if (it->get_status() == DEAD) {
        it = q.erase(it);
        continue;
      } else if (it->get_status() == REPRODUCING) {
        int adjacent[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
          int x = it->x+adjacent[i][0];
          int y = it->y+adjacent[i][1];
          if (Cell::check_status(x, y) == NONE) {
            Cell new_cell = Cell(it->get_period(), x, y);
            new_cells.push_back(new_cell);
          } else if (Cell::check_status(x, y) == DISABLED) {
            Cell existing_cell(x, y);
            existing_cell.set_period(it->get_period());
          }
        }
        if (it->get_period() == 1)
          it->kill();
        else
          it->set_status(ALIVE);
      }
      it++;
    }
    for (Cell each : new_cells)
      q.push_back(each);
  }
  printf("#%d %d\n", testcase, Cell::get_cnt());
}


int main () {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve (i);
  return 0;

}
