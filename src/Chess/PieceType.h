#pragma once

enum PieceType {
    EMPTY = -1,	
    PAWN = 0,
    ROOK = 1,
    KNIGHT = 2,
    BISHOP = 3,
    QUEEN = 4,
    KING = 5
};

const char EMPTY_SYMBOL = ' ';
const char PAWN_SYMBOL = 'P';
const char ROOK_SYMBOL = 'R';
const char KNIGHT_SYMBOL = 'N';
const char BISHOP_SYMBOL = 'B';
const char QUEEN_SYMBOL = 'Q';
const char KING_SYMBOL = 'K';

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
