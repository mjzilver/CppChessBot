#pragma once

enum PieceType { EMPTY = -1, PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5 };

constexpr char EMPTY_SYMBOL = ' ';
constexpr char PAWN_SYMBOL = 'P';
constexpr char ROOK_SYMBOL = 'R';
constexpr char KNIGHT_SYMBOL = 'N';
constexpr char BISHOP_SYMBOL = 'B';
constexpr char QUEEN_SYMBOL = 'Q';
constexpr char KING_SYMBOL = 'K';

inline char pieceTypeToSymbol(const PieceType type) {
    switch (type) {
        case PAWN:
            return PAWN_SYMBOL;
        case ROOK:
            return ROOK_SYMBOL;
        case KNIGHT:
            return KNIGHT_SYMBOL;
        case BISHOP:
            return BISHOP_SYMBOL;
        case QUEEN:
            return QUEEN_SYMBOL;
        case KING:
            return KING_SYMBOL;
        default:
            return EMPTY_SYMBOL;
    }
}
