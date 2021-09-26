class Board {
    public:
        Board();
        void PrintArr(void);
        void Insert(bool turn_);
        bool Monkey(int num_);
        bool Check(bool turn_);
    private :
        static const int ROW = 6, COLUMN = 7;
        char arr[ROW][COLUMN];   
};