#ifndef QUESTION_H
#define QUESTION_H

struct Question
{
	int id_;
	std::string stem_;
	std::string option_[4];
	char answer_;

	bool verifyAnswer(char ans) const
	{
		return answer_ == ans;
	}
};

#endif /* QUESTION_H */
