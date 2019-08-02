#include "guessGame.h"

int guessGamePlayer1Score = 0;
int guessGamePlayer2Score = 0;

std::string questions[] = {
    /*0*/"ALU stands for...",
    /*1*/"CPU stands for...",
    /*2*/"What does OTG stands for?",
    /*3*/"NFC stands for...",
    /*4*/"ROM stand for...",
    /*5*/"RAM stands for...",
    /*6*/"Which of these sorting algorithms is the fastest?",
    /*7*/"An n-bit microprocessor has..",
    /*8*/"HTML stands for...",
    /*9*/"What is the Cascading stylesheet file extension?",
    /*10*/"What is the MS-DOS batch file extension?",
    /*11*/".jsp is the extension of which file?",
    /*12*/".jar is the extension of which file?",
    /*13*/"The extension for compiled java source code file is",
    /*14*/".dll is the extension of which file?",
    /*15*/"The extension of a database file is...",
    /*16*/"Which of the following is an input device?",
    /*17*/"Which of the following is an input device?",
    /*18*/"Which of the following is an output device?",
    /*19*/"Which of the following is an output device?",
    /*20*/"Every Web page has a unique address called...",
    /*21*/"A computer on the internet is indetified by..."
    /*22*/
};

std::string answers[][3] = {
    /*0*/{"Arithmetic Long Unit", "Arithmetic and Logic Unit", "All longer Units"},
    /*1*/{"Central Periphral Unit", "Central Printing Unit", "Central Processing Unit"},
    /*2*/{"On-the-go", "On-the-gone", "One-the-go"},
    /*3*/{"No field communication", "Near field communication", "Near-far communication"},
    /*4*/{"Random only memory", "Read only memory", "Rapid on memory"},
    /*5*/{"Random access memory", "Read axis memory", "Read access memory"},
    /*6*/{"Bubble sort", "Insertion sort", "Quick sort"},
    /*7*/{"n-bit ALU", "n-bit instruction register", "n-bit address register"},
    /*8*/{"Hypertext Markup Language", "Hypertext Markdown Language", "Hyper Max Language"},
    /*9*/{".cpp", ".css", ".cs"},
    /*10*/{".bd", ".dos", ".bat"},
    /*11*/{"JavaScript code file", "Java language file", "Java Server Page file"},
    /*12*/{"Java language file", "Java classes archive file", "CVS journal file"},
    /*13*/{".class", ".java", ".cpp"},
    /*14*/{"XP dynamic linked library", "Win32 dynamic linked library", "Win32 dialog resource file"},
    /*15*/{".dta", "data", ".db"},
    /*16*/{"monitor", "mouse", "printer"},
    /*17*/{"keyboard", "speaker", "projector"},
    /*18*/{"keyboard", "JoyStick", "monitor"},
    /*19*/{"bar code reader", "scanner", "headphones"},
    /*20*/{"RUL", "URL", "ARL"},
    /*21*/{"IP address", "email address", "street address"}
    /*22*/

};

int rightAnswers[] = {
    /*0*/1,
    /*1*/2,
    /*2*/0,
    /*3*/1,
    /*4*/1,
    /*5*/0,
    /*6*/2,
    /*7*/2,
    /*8*/0,
    /*9*/1,
    /*10*/2,
    /*11*/2,
    /*12*/1,
    /*13*/0,
    /*14*/1,
    /*15*/2,
    /*16*/1,
    /*17*/0,
    /*18*/2,
    /*19*/2,
    /*20*/1,
    /*21*/0

};

void guessGameMenu(cv::VideoCapture cap)
{
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    const std::string line1 = "Guess Game";
    const std::string line2 = "You will get one question at a time";
    const std::string line3 = "with 3 possible answers";
    const std::string line4 = "Try to hit the right answer";
    const std::string line5 = "as fast as you can";
    const std::string line6 = "START";
    int fontFace = cv::FONT_HERSHEY_TRIPLEX;
    int fontScale2 = 2;
    int fontScale3 = 3;
    int thickness = 5;
    int baseLine = 0;
    cv::Size line1Size = cv::getTextSize(line1, fontFace, fontScale3, thickness, &baseLine);
    cv::Size line2Size = cv::getTextSize(line2, fontFace, fontScale2, thickness, &baseLine);
    cv::Size line3Size = cv::getTextSize(line3, fontFace, fontScale2, thickness, &baseLine);
    cv::Size line4Size = cv::getTextSize(line4, fontFace, fontScale2, thickness, &baseLine);
    cv::Size line5Size = cv::getTextSize(line5, fontFace, fontScale2, thickness, &baseLine);
    cv::Size line6Size = cv::getTextSize(line6, fontFace, fontScale2, thickness, &baseLine);

    cv::Mat frame;

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point1 = coord(frame, player1);
        cv::Point point2 = coord(frame, player2);

        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
        cv::putText(frame, line1, cv::Point(width / 2 - (line1Size.width / 2) + 5, line1Size.height + 15), cv::FONT_HERSHEY_TRIPLEX, 3, cv::Scalar(0, 0, 0), 5);
        cv::putText(frame, line1, cv::Point(width / 2 - (line1Size.width / 2), line1Size.height + 10), cv::FONT_HERSHEY_TRIPLEX, 3, cv::Scalar(255, 255, 255), 5);
        int x = line1Size.height + 15;
        cv::putText(frame, line2, cv::Point(width / 2 - (line2Size.width / 2) + 5, x + line2Size.height + 15), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 3);
        cv::putText(frame, line2, cv::Point(width / 2 - (line2Size.width / 2), x + line2Size.height + 10), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 3);
        x += line2Size.height + 15;
        cv::putText(frame, line3, cv::Point(width / 2 - (line3Size.width / 2) + 5, x + line3Size.height + 15), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 3);
        cv::putText(frame, line3, cv::Point(width / 2 - (line3Size.width / 2), x + line3Size.height + 10), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 3);
        x += line3Size.height + 15;
        cv::putText(frame, line4, cv::Point(width / 2 - (line4Size.width / 2) + 5, x + line4Size.height + 15), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 3);
        cv::putText(frame, line4, cv::Point(width / 2 - (line4Size.width / 2), x + line4Size.height + 10), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 3);
        x += line4Size.height + 15;
        cv::putText(frame, line5, cv::Point(width / 2 - (line5Size.width / 2) + 5, x + line5Size.height + 15), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 3);
        cv::putText(frame, line5, cv::Point(width / 2 - (line5Size.width / 2), x + line5Size.height + 10), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 3);
        x += line5Size.height + 15;
        cv::putText(frame, line6, cv::Point(width / 2 - (line6Size.width / 2) + 5, x + 6 * line6Size.height + 5), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 3);
        cv::putText(frame, line6, cv::Point(width / 2 - (line6Size.width / 2), x + 6 * line6Size.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 3);

        cv::Point startButton = (cv::Point(width / 2 - (line6Size.width / 2), x + 6 * line6Size.height));

        cv::imshow("Cinekt", frame);

        if (point1.x >= (startButton.x) && point1.x <= (startButton.x + line6Size.width) && point1.y <= startButton.y && point1.y >= (startButton.y - line6Size.height)) {
            return;
        }

        if (cv::waitKey(16) == 27) {
            return;
        }
    }
}

void guessGameNewQuestionPreparation(cv::VideoCapture cap)
{
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::Mat frame;

    cv::Point point1;
    cv::Point point2;

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        point1 = coord(frame, player1);
        point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);

        cv::Size scoreTextSize = cv::getTextSize("Go to your corners!", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
        cv::putText(frame, "Go to your corners!", cv::Point(width / 2 - (scoreTextSize.width / 2) + 3, height / 2 + 3), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2, 8, false);
        cv::putText(frame, "Go to your corners!", cv::Point(width / 2 - (scoreTextSize.width / 2), height / 2), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2, 8, false);

        cv::rectangle(frame, cv::Point(1, height - 121), cv::Point(121, height - 1), cv::Scalar(0, 0, 255), 3);
        cv::putText(frame, std::to_string(guessGamePlayer1Score), cv::Point(8, height - 7), cv::FONT_HERSHEY_TRIPLEX, 5, cv::Scalar(0, 0, 0), 5);
        cv::putText(frame, std::to_string(guessGamePlayer1Score), cv::Point(5, height - 10), cv::FONT_HERSHEY_TRIPLEX, 5, cv::Scalar(255, 255, 255), 5);
        cv::rectangle(frame, cv::Point(width - 121, height - 121), cv::Point(width - 1, height - 1), cv::Scalar(255, 0, 0), 3);

        
        if (point1.x < 151 && point1.y >(height - 151) && point2.x > (width - 151) && point2.y > (height - 151)) {
            break;
        }
        
        cv::imshow("Cinekt", frame);
        if (cv::waitKey(16) == 27) {
            return;
        }
    }

}

void guessGamePlay(cv::VideoCapture cap)
{
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::Mat frame;

    bool newQuestion = true;
    int random;

    cv::Point point1(0, height);
    cv::Point point2(width, height);

    cv::Size questionSize;
    cv::Size answer0Size;
    cv::Size answer1Size;
    cv::Size answer2Size;

    cv::Point questionPosition;
    cv::Point answer0Position;
    cv::Point answer1Position;
    cv::Point answer2Position;

    std::vector<cv::Point> currentAnswerPositions;
    std::vector<cv::Size> currentAnswerSizes;

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        point1 = coord(frame, player1);
        point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);

        /*Calculate data for new question*/
        if (newQuestion) {
            random = rand() % 22;
            newQuestion = false;
            int baseLine = 0;
            questionSize = cv::getTextSize(questions[random], cv::FONT_HERSHEY_TRIPLEX, 1.3, 1, &baseLine);
            answer0Size = cv::getTextSize(answers[random][0], cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
            answer1Size = cv::getTextSize(answers[random][1], cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
            answer2Size = cv::getTextSize(answers[random][2], cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);

            currentAnswerSizes.clear();
            currentAnswerSizes.push_back(answer0Size);
            currentAnswerSizes.push_back(answer1Size);
            currentAnswerSizes.push_back(answer2Size);

            questionPosition = cv::Point(width / 2 - (questionSize.width / 2), questionSize.height + 15);
            answer0Position = cv::Point(width / 2 - (answer0Size.width / 2), questionPosition.y + 3 * answer0Size.height);
            answer1Position = cv::Point(width / 2 - (answer1Size.width / 2), answer0Position.y + 3 * answer1Size.height);
            answer2Position = cv::Point(width / 2 - (answer2Size.width / 2), answer1Position.y + 3 * answer2Size.height);

            currentAnswerPositions.clear();
            currentAnswerPositions.push_back(answer0Position);
            currentAnswerPositions.push_back(answer1Position);
            currentAnswerPositions.push_back(answer2Position);
        }

        /*Show question*/
        cv::putText(frame, questions[random], cv::Point(questionPosition.x + 3, questionPosition.y + 3), cv::FONT_HERSHEY_TRIPLEX, 1.3, cv::Scalar(0, 0, 0), 1, 8, false);
        cv::putText(frame, questions[random], cv::Point(questionPosition.x, questionPosition.y), cv::FONT_HERSHEY_TRIPLEX, 1.3, cv::Scalar(255, 255, 255), 1, 8, false);

        cv::putText(frame, answers[random][0], cv::Point(answer0Position.x + 3, answer0Position.y + 3), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2, 8, false);
        cv::putText(frame, answers[random][0], cv::Point(answer0Position.x, answer0Position.y), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2, 8, false);

        cv::putText(frame, answers[random][1], cv::Point(answer1Position.x + 3, answer1Position.y + 3), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2, 8, false);
        cv::putText(frame, answers[random][1], cv::Point(answer1Position.x, answer1Position.y), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2, 8, false);

        cv::putText(frame, answers[random][2], cv::Point(answer2Position.x + 3, answer2Position.y + 3), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2, 8, false);
        cv::putText(frame, answers[random][2], cv::Point(answer2Position.x, answer2Position.y), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2, 8, false);

        /*Check winner*/
        cv::Point currentRightAnswerPosition = currentAnswerPositions[rightAnswers[random]];
        cv::Size currentRightAnswerSize = currentAnswerSizes[rightAnswers[random]];

        if (point1.x >= currentRightAnswerPosition.x && point1.x <= currentRightAnswerPosition.x + currentRightAnswerSize.width &&
            point1.y >= currentRightAnswerPosition.y - currentRightAnswerSize.height && point1.y <= currentRightAnswerPosition.y) {
            newQuestion = true;
            cv::Size scoreTextSize = cv::getTextSize("Player 1 scores!", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
            cv::putText(frame, "Player 1 scores!", cv::Point(width / 2 - (scoreTextSize.width / 2), height - 20), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 255), 2, 8, false);
            guessGamePlayer1Score++;
            cv::imshow("Cinekt", frame);
            cv::waitKey(1500);
        }

        if (point2.x >= currentRightAnswerPosition.x && point2.x <= currentRightAnswerPosition.x + currentRightAnswerSize.width &&
            point2.y >= currentRightAnswerPosition.y - currentRightAnswerSize.height && point2.y <= currentRightAnswerPosition.y) {
            newQuestion = true;
            cv::Size scoreTextSize = cv::getTextSize("Player 2 scores!", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
            cv::putText(frame, "Player 2 scores!", cv::Point(width / 2 - (scoreTextSize.width / 2), height - 20), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 0, 0), 2, 8, false);
            cv::imshow("Cinekt", frame);
            guessGamePlayer2Score++;
            cv::waitKey(1500);
        }
        
        if (newQuestion) {
            guessGameNewQuestionPreparation(cap);
        }

        cv::imshow("Cinekt", frame);

        if (cv::waitKey(5) == 27) {
            return;
        }

    }
}

void guessGameOver(cv::VideoCapture cap)
{
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::Mat frame;
    /*
    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point1 = coord(frame, player1);
        cv::Point point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
    }
    */
}

void guessGame(cv::VideoCapture cap)
{
    while (true) {
        guessGameMenu(cap);
        guessGamePlay(cap);
        guessGameOver(cap);



        /*
        if (cv::waitKey(16) == 27) {
            return;
        }
        */
        return;
    }
}