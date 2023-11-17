#define RAYSUITE_NO_MATH
#include "raysuite.h"

#define TRUE 1
#define FALSE 0

#define TOTAL_NUMBERS 80
#define NUMBERS_PER_ROUND 20
#define SECONDS_TILL_NUMBER 1.0f
#define SECONDS_PER_ROUND 60.0f // 2 minutes

int* numbers;

float round_timer, number_timer;

int numbers_counted, last_number_selected;
int heads_counted, tails_counted;

void ResetGame ();

int main (int argc, const char* argv[]) {
    SetTraceLogLevel (LOG_ERROR);
    SetTargetFPS (30);

    InitWindow (960, 540, "Open-Keno");

    numbers = RL_MALLOC (sizeof (int) * TOTAL_NUMBERS);
    ResetGame ();

    while (!WindowShouldClose ()) {
        float delta_time = GetFrameTime ();;

        round_timer -= delta_time;
        if (round_timer <= 0.0f) {
            ResetGame ();
        }

        if (numbers_counted < NUMBERS_PER_ROUND) {
            number_timer -= delta_time;

            if (number_timer <= 0.0f) {
                number_timer = SECONDS_TILL_NUMBER;

                last_number_selected = GetRandomValue (1, TOTAL_NUMBERS - 1);

                while (numbers[last_number_selected]) {
                    last_number_selected = GetRandomValue (1, TOTAL_NUMBERS - 1);
                }

                numbers[last_number_selected] = true;
                numbers_counted++;

                // This feels wrong...
                last_number_selected <= 40 ? heads_counted++ : tails_counted++;
            }
        }

        BeginDrawing ();
            ClearBackground (RAYWHITE);

            int current_number = 0;

            #define NUMBERS_ROWS 8
            #define NUMBERS_PER_ROW 10
            #define PADDING 54

            Color colour;

            for (int i = 0; i < NUMBERS_ROWS; i++) {
                for (int j = 0; j < NUMBERS_PER_ROW; j++) {
                    if (numbers[current_number]) {
                        colour = RED;
                    } else {
                        colour = BLACK;
                    }

                    DrawText (TextFormat ("%d", current_number + 1), 16 + (j * PADDING), 16 + (i * PADDING), 30, colour);

                    current_number++;
                }
            }

            DrawText (TextFormat ("Heads: %d", heads_counted), 600, 16, 30, BLACK);
            DrawText (TextFormat ("Tails: %d", tails_counted), 600, 70, 30, BLACK);

            if (last_number_selected > 0 && numbers_counted < 20) {
                DrawText (TextFormat ("%d", last_number_selected + 1), 600, 340, 100, BLACK);
            }
        EndDrawing ();
    }

    RL_FREE (numbers);

    CloseWindow ();

    return 0;
}

void ResetGame () {
    for (int i = 0; i < TOTAL_NUMBERS; i++) numbers[i] = false;

    round_timer = SECONDS_PER_ROUND;
    number_timer = SECONDS_TILL_NUMBER;

    numbers_counted = 0;
    last_number_selected = 0;

    heads_counted = 0;
    tails_counted = 0;
}
