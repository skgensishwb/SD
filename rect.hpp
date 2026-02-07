class Rect {
    private:
        float m_leftBorder;
        float m_rightBorder;
        float m_upperBorder;
        float m_lowerBorder;

    public:
        inline int get_left() { return m_leftBorder; }
        inline int get_right() { return m_rightBorder; }
        inline int get_top() { return m_upperBorder; }
        inline int get_bottom() { return m_lowerBorder; }
        
        void set_all(int left, int right, int top, int bottom);

        Rect(float m_leftBorder, float m_rightBorder, float m_upperBorder, float m_lowerBorder);
        Rect();
        Rect(const Rect& other);
        ~Rect();
};