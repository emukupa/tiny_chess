#pragma once

#define NO_UNIT 0
#define WHITE 0x10
#define BLACK 0x20
#define OUT_OF_BOARD 0xFF

#define WHITE_OR_BLACK_MASK (WHITE|BLACK)

#define KING 1
#define QUEEN 2
#define ROOK 3
#define BISHOP 4
#define KNIGHT 5
#define PAWN 6

#define WHITE_KING (WHITE|KING)
#define WHITE_QUEEN (WHITE|QUEEN)
#define WHITE_ROOK (WHITE|ROOK)
#define WHITE_BISHOP (WHITE|BISHOP)
#define WHITE_KNIGHT (WHITE|KNIGHT)
#define WHITE_PAWN (WHITE|PAWN)
#define BLACK_KING (BLACK|KING)
#define BLACK_QUEEN (BLACK|QUEEN)
#define BLACK_ROOK (BLACK|ROOK)
#define BLACK_BISHOP (BLACK|BISHOP)
#define BLACK_KNIGHT (BLACK|KNIGHT)
#define BLACK_PAWN (BLACK|PAWN)

#define SOLID_COLOR_TEXTURE 0
#define WHITE_KING_TEXTURE 1
#define WHITE_QUEEN_TEXTURE 2
#define WHITE_ROOK_TEXTURE 3
#define WHITE_BISHOP_TEXTURE 4
#define WHITE_KNIGHT_TEXTURE 5
#define WHITE_PAWN_TEXTURE 6
#define BLACK_KING_TEXTURE 7
#define BLACK_QUEEN_TEXTURE 8
#define BLACK_ROOK_TEXTURE 9
#define BLACK_BISHOP_TEXTURE 10
#define BLACK_KNIGHT_TEXTURE 11
#define BLACK_PAWN_TEXTURE 12
#define NUM_TEXTURES 13
#define IS_TEXTURE_FOR_WHITE_PIECE(tex) ((tex) >= WHITE_KING_TEXTURE && (tex) <= WHITE_PAWN_TEXTURE)

#define IS_WHITE_PIECE(piece) (((piece) & WHITE_OR_BLACK_MASK) == WHITE)
#define IS_BLACK_PIECE(piece) (((piece) & WHITE_OR_BLACK_MASK) == BLACK)

// Returns WHITE or BLACK, NO_UNIT or OUT_OF_BOARD
#define PLAYER_COLOR(piece) ((piece) & WHITE_OR_BLACK_MASK)

// Maps WHITE to BLACK and vice versa, don't call with other enums
#define OPPONENT_COLOR(player_color) (((~(player_color)) & WHITE_OR_BLACK_MASK))

#define PIECE_TYPE(piece) ((piece) & ~WHITE_OR_BLACK_MASK)

// player_color == WHITE or BLACK don't call with other enums
#define IS_EMPTY_OR_OPPONENT(player_color, piece) (((piece) & (player_color)) == 0)

#define IS_OPPONENT(player_color, piece) ((PLAYER_COLOR(piece) ^ (player_color)) == (WHITE|BLACK))

#define KING_AT_HOME 0x1
#define KING_ROOK_AT_HOME 0x2
#define QUEEN_ROOK_AT_HOME 0x4
#define KINGSIDE_CASTLING_MASK (KING_AT_HOME|KING_ROOK_AT_HOME)
#define QUEENSIDE_CASTLING_MASK (KING_AT_HOME|QUEEN_ROOK_AT_HOME)

struct Board
{
public:
  int out;
  int piece[8][8];
  int currentPlayer;
  int castlingPiecesAtHome[2];

  int enpassantX, enpassantY;

  int &At(int x, int y) { return (x >= 0 && x < 8 && y >= 0 && y < 8) ? piece[y][x] : out; }
  int At(int x, int y) const { return (x >= 0 && x < 8 && y >= 0 && y < 8) ? piece[y][x] : out; }

  void init();

  bool find_first_piece(int piece, int *x, int *y);

  bool is_king_in_check(int color);

  // Applies the given move without checking for its legality.
  void make_move(int srcX, int srcY, int dstX, int dstY);

  // moves must be at least 3*8*2 = 48 ints long. Returns number of moves generated.
  int generate_moves(int x, int y, int *moves);
  int generate_moves_without_king_safety(int x, int y, int *moves);

  int generate_pawn_moves(int x, int y, int *moves);
  int generate_knight_moves(int x, int y, int *moves);
  int generate_rook_moves(int x, int y, int *moves);
  int generate_bishop_moves(int x, int y, int *moves);
  int generate_queen_moves(int x, int y, int *moves);
  int generate_king_moves(int x, int y, int *moves);

  void mark_controlled_squares(int color, int squares[8][8]);

  void mark_pawn_controlled_squares(int x, int y, int squares[8][8]);
  void mark_knight_controlled_squares(int x, int y, int squares[8][8]);
  void mark_rook_controlled_squares(int x, int y, int squares[8][8]);
  void mark_bishop_controlled_squares(int x, int y, int squares[8][8]);
  void mark_queen_controlled_squares(int x, int y, int squares[8][8]);
  void mark_king_controlled_squares(int x, int y, int squares[8][8]);
};
