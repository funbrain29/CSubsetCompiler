#define ShowMessages 0

#if ShowMessages == 1
#define MSG(X) std::cout << X
#endif

#if ShowMessages == 0
#define MSG(X)
#endif