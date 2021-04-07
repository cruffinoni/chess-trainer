
#include <algorithm>
#include "PGN.hpp"

bool ChessTrainer::Notation::PGN::readTags(std::string& line) {
    bool tagOpened = false;
    bool tagContentOpened = false;
    std::string tagContent;
    std::string tagTitle;

    // Split by line instead of by char
    for (const auto& c: line) {
        if (c == '[') {
            if (tagOpened)
                return this->invalidate("trying to open another tag while one is already opened");
            tagOpened = true;
            continue;
        } else if (c == '\"') {
            if (!tagOpened)
                return this->invalidate("tag must be open to read content: extra quote");
            tagContentOpened = !tagContentOpened;
            continue;
        }
        if (c == ']') {
            if (!tagOpened)
                return this->invalidate("tag not opened: extra closing ]");
            tagOpened = false;
            this->tags_.emplace_back(tagTitle, tagContent);
            continue;
        }
        if (tagContentOpened)
            tagContent += c;
        else if (!std::isspace(c))
            tagTitle += c;
    }
    if (tagContentOpened)
        return this->invalidate("tag content non closed, a quote is missing");
    if (tagOpened)
        return this->invalidate("tag not closed");
    if (tagTitle.empty())
        return this->invalidate("missing tag title");
    if (tagContent.empty())
        return this->invalidate("tag with no content");
    return true;
}

bool ChessTrainer::Notation::PGN::invalidate(const std::string& reasons) {
    std::cerr << "Invalid PGN: " << reasons << std::endl;
    this->valid_ = false;
    return false;
}

ChessTrainer::Notation::PGN::PGN(std::string input): board_(IPiece::Color::White) {
    this->readTags(input);

    std::cout << "Tags:" << std::endl;
    for (const auto& t : this->tags_)
        std::cout << "'" << t.first << "' > '" << t.second << "'" << std::endl;
}

bool ChessTrainer::Notation::PGN::isValid() const {
    return this->valid_;
}
