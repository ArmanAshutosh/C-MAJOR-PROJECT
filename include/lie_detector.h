
#ifndef LIE_DETECTOR_H
#define LIE_DETECTOR_H

#define QUESTION_LEN 256
#define ANSWER_LEN 64

typedef struct {
    char *question;
    char expected[ANSWER_LEN];
    char answer[ANSWER_LEN];
    double response_time;
    int correct;     // 1 = lie, 0 = truthful
} Question;

void trim_newline(char *s);
void str_tolower(char *s);
int ci_equal(const char *a, const char *b);

#endif
