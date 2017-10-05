#define mathLib_h

class point2D {
public: 
    point2D();
    point2D(float inX, float inY);
    float x;
    float y;
};

class vec2D {
public:
    vec2D();
    vec2D(float inX, float inY);
    float inX;
    float inY;
    magnitude();
};

class mathLib() {
public:
    mathLib();
    static float distance(point2D start, point2D end);
    static vec2D normalize(vec2D);
};

#endif /* mathLib_h */