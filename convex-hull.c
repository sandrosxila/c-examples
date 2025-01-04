#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  long long x;
  long long y;
} Point;

// Line drawn from 'a' to 'b' to 'c'. We make use of the cross product, which calculates the area of the parallelogram.
int ccw(Point a, Point b, Point c) {
  float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

  if (area < 0)
    return -1; // clockwise

  if (area > 0)
    return 1; // counter-clockwise

  return 0; // collinear
}

Point refPoint; // a global variable which will be set in the main function
int compare(const void * a, const void * b) {
  Point p1 = * (Point *)(a);
  Point p2 = * (Point *)(b);

  if (p1.x == refPoint.x && p1.y == refPoint.y)
    return -1;

  if (p2.x == refPoint.x && p2.y == refPoint.y)
    return 1;

  int is_ccw = ccw(refPoint, p1, p2);

  if (is_ccw == 0) {
    return p1.x == p2.x ? p2.y - p1.y : p2.x - p1.x;
  }

  return is_ccw * -1;
}

void initRefPoint(Point points[], int n) {
  // get refPoint
  refPoint.x = INT_MAX;
  refPoint.y = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (refPoint.y == points[i].y) {
      if (refPoint.x > points[i].x) {
        refPoint.x = points[i].x;
      }
      continue;
    }

    if (refPoint.y > points[i].y) {
      refPoint = points[i];
    }
  }
}

void scan(Point points[], int n, int idx_stack[], int *res_size) {
  initRefPoint(points, n); // bottom most, left most point

  // sort by angle with respect to refPoint
  qsort(points, n, sizeof(Point), compare);
  
  int top = 0;
  idx_stack[top++] = 0; // 1st point is guaranteed to be on the hull
  idx_stack[top++] = 1; // don't know about this one yet

  for (int i = 2; i < n; i++) {
    Point next = points[i];

    int pIdx = idx_stack[--top];
    Point p = points[pIdx];

    int peekIdx = idx_stack[top - 1];
    Point peek = points[peekIdx];

    while (top != 0 && ccw(peek, p, next) < 1) {
      pIdx = idx_stack[--top];
      p = points[pIdx]; // delete the points that create clockwise turn

      peekIdx = idx_stack[top - 1];
      peek = points[peekIdx];
    }

    idx_stack[top++] = pIdx;
    idx_stack[top++] = i;
  }

  // the very last point pushed in could have been collinear, so we check for that
  int pIdx = idx_stack[--top];
  Point p = points[pIdx];

  int peekIdx = idx_stack[top - 1];
  Point peek = points[peekIdx];

  if (ccw(peek, p, refPoint) > 0) {
    idx_stack[top++] = pIdx;  // put it back, everything is fine
  }

  *res_size = top;
}

Point *findConvexHull(int points_list[][2], const int n, int* res_size) {
  Point points[n];
  int idx_stack[n];

  for (int i = 0; i < n; i++) {
    points[i].x = points_list[i][0];
    points[i].y = points_list[i][1];
  }

  scan(points, n, idx_stack, res_size); // perform graham scan

  Point *returnValues = malloc((*res_size) * sizeof(Point));

  if (*res_size < 3) {
    *res_size = 0;
    return returnValues;
  }

  for (int i = 0; i < *res_size; i++) {
    int pIdx = idx_stack[i];
    returnValues[i] = points[pIdx];
  }

  return returnValues;
}

int main() {
    int data[][2] = {
      {-93920, 85455},
      {-43108, -74185},
      {18291, 71652},
      {47356, 5717},
      {-46000, -94661},
      {98014, -31009},
      {-76446, -86311},
      {19084, 11900}
    };

  int arrSize;
  Point * arr = findConvexHull(data, sizeof(data) / sizeof(data[0]), &arrSize);

  for(int i = 0; i < arrSize; i++) {
    printf("%lld %lld\n", arr[i].x, arr[i].y);
  }

  free(arr);
  return 0;
}