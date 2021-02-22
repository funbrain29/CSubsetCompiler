#define ShowMessages 1

#if ShowMessages == 1
#define MSG(X) std::cout << X << std::endl
#endif

#if ShowMessages == 0
#define MSG(X)
#endif