#include "Challenge.hpp"

 Challenge::Challenge(string tag) : tag(tag) {

}

 void Challenge::finish(float rating) {
    times_finished++;
    score = score + (rating - score) / times_finished;
}

 void Challenge::challenge() {
    times_challenged++;
}

std::ostream& operator<<(std::ostream& output, Challenge& s) {
	std::cout << std::left << std::setw(15) << s.tag;
	std::cout << std::left << std::setw(15) << s.score;
	std::cout << std::left << std::setw(15) << (s.times_challenged == 1 ? "new" : s.times_challenged < 11 ? "quite recently" : "old");
	std::cout << std::left << std::setw(15) << s.times_challenged;
	std::cout << std::left << std::setw(15) << s.times_finished;
	return output;
}