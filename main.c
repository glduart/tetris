#include <stdio.h>
#include <stdlib.h>

#define LINES 20
#define COLUMNS 10

typedef int screen[LINES][COLUMNS];

typedef struct {
  int **shape;
  int width;
  int height;
} Piece;

Piece *createPiece(int **shape, int width, int height) {
  Piece *piece = (Piece *)malloc(sizeof(Piece));

  if (piece == NULL) {
    exit(EXIT_FAILURE);
  }

  piece->shape = shape;
  piece->width = width;
  piece->height = height;
  return piece;
}

void freePiece(Piece *piece) {
  for (int i = 0; i < piece->height; i++) {
    free(piece->shape[i]);
  }
  free(piece->shape);
  free(piece);
}

void displayGame(screen screen) {
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      switch (screen[i][j]) {
      case 0:
        printf(". ");
        break;
      case 1:
        printf("+ ");
        break;
      }
    }
    printf("\n");
  }
}

void initializeScreen(screen screen) {
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      screen[i][j] = 0;
    }
  }
}

void downPiece(screen screen, Piece *piece) {
  int downLines = LINES - 1;
  int height = piece->height;
  int y_position = 4;
  for (int i = 1; i < downLines; i++) {
    int x = piece->height + i;
    for (int j = 0; j < piece->height; j++) {
      x--;
      int y = 4;
      for (int k = 0; k < piece->width; k++) {
        screen[x][y] = piece->shape[j][k];
        screen[x - 1][y] = 0;
        y++;
      }
    }
    displayGame(screen);
    printf("\n");
    printf("\n");
  }
}

void insertPiece(screen screen, Piece *piece) {
  int x = piece->height;
  for (int i = 0; i < piece->height; i++) {
    x--;
    int y = 4;
    for (int j = 0; j < piece->width; j++) {
      screen[x][y] = piece->shape[i][j];
      y++;
    }
  }
  displayGame(screen);
  printf("\n");
  printf("\n");
}

Piece *createTriangle() {
  int triangleShape[2][3] = {{1, 1, 1}, {0, 1, 0}};
  int **shape = (int **)malloc(sizeof(int *) * 2);

  if (shape == NULL) {
    return EXIT_FAILURE;
  }

  for (int i = 0; i < 2; i++) {
    shape[i] = (int *)malloc(sizeof(int) * 3);

    if (shape[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(shape[j]);
      }
      free(shape);
      exit(EXIT_FAILURE);
    }
  }

  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 3; k++) {
      shape[j][k] = triangleShape[j][k];
    }
  }

  return createPiece(shape, 3, 2);
}

int main() {
  int screen[LINES][COLUMNS];
  initializeScreen(screen);

  Piece *piece = createTriangle();

  insertPiece(screen, piece);
  downPiece(screen, piece);

  freePiece(piece);

  return EXIT_SUCCESS;
}
