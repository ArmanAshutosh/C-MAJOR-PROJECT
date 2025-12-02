// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lie_detector.h"

int main(void) {
    int n = 5;
    double time_threshold = 3.0;

    Question *qs = malloc(sizeof(Question) * n);
    if (!qs) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    const char *questions_text[] = {
        "Did you take the money? (yes/no): ",
        "Are you over 18? (yes/no): ",
        "Did you finish your work? (yes/no): ",
        "Is your name Arman? (yes/no): ",
        "Do you like pizza? (yes/no): "
    };

    const char *expected_answers[] = {
        "no",
        "yes",
        "yes",
        "yes",
        "yes"
    };

    for (int i = 0; i < n; ++i) {
        qs[i].question = malloc(strlen(questions_text[i]) + 1);
        strcpy(qs[i].question, questions_text[i]);

        strncpy(qs[i].expected, expected_answers[i], ANSWER_LEN - 1);
        qs[i].expected[ANSWER_LEN - 1] = '\0';

        qs[i].answer[0] = '\0';
        qs[i].response_time = 0.0;
        qs[i].correct = 0;
    }

    printf("=== Simple C Lie Detector (Simulation) ===\n");
    printf("You will be asked %d questions.\n\n", n);

    for (int i = 0; i < n; ++i) {
        char buffer[QUESTION_LEN];

        printf("%s", qs[i].question);
        fflush(stdout);

        clock_t start = clock();
        if (!fgets(buffer, sizeof buffer, stdin))
            buffer[0] = '\0';
        clock_t end = clock();

        trim_newline(buffer);

        strncpy(qs[i].answer, buffer, ANSWER_LEN - 1);
        qs[i].answer[ANSWER_LEN - 1] = '\0';
        str_tolower(qs[i].answer);

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        qs[i].response_time = elapsed;

        if (!ci_equal(qs[i].answer, qs[i].expected) || elapsed > time_threshold)
            qs[i].correct = 1;
    }

    printf("\n=== Results ===\n");
    int lies = 0;

    for (int i = 0; i < n; ++i) {
        printf("Q%d: %s\n", i + 1, qs[i].question);
        printf("   Expected: %s | Answer: %s | Time: %.2fs -> %s\n",
               qs[i].expected,
               qs[i].answer[0] ? qs[i].answer : "(no answer)",
               qs[i].response_time,
               qs[i].correct ? "Possible LIE" : "Truthful");

        if (qs[i].correct) lies++;
    }

    printf("\nOverall: %d out of %d answers flagged as possible lies.\n", lies, n);

    for (int i = 0; i < n; ++i)
        free(qs[i].question);

    free(qs);
    return 0;
}
