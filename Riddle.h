class Riddle {
private:
    std::string question;
    std::string answer;
    std::string bonusQuestion;
    std::string bonusAnswer;

public:
    // Regular riddle constructor
    Riddle(std::string parseLine) {
        std::stringstream ss(parseLine);
        std::string token;

        if (std::getline(ss, token, '|')) question = token;
        if (std::getline(ss, token, '|')) answer = token;
    }

    // Bonus riddle constructor
    Riddle(std::string parseLine, bool isBonus) {
        std::stringstream ss(parseLine);
        std::string token;

        if (std::getline(ss, token, '|')) bonusQuestion = token;
        if (std::getline(ss, token, '|')) bonusAnswer = token;
    }

    std::string getQuestion() { return question; }
    std::string getAnswer() { return answer; }
    std::string getBonusQuestion() { return bonusQuestion; }
    std::string getBonusAnswer() { return bonusAnswer; }
};
