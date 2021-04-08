
#include <algorithm>
#include "PGN.hpp"
#include "../../Utils.hpp"

bool ChessTrainer::Notation::PGN::readTags(std::string& input) {
    bool tagOpened = false;
    bool tagContentOpened = false;
    std::string tagContent;
    std::string tagTitle;
    const auto& lines = ChessTrainer::Utils::splitString(input, '\n');

    for (const auto& line: lines) {
        if (line.empty())
            break;
        for (const auto& c: line) {
            if (c == '[') {
                if (tagOpened)
                    return this->invalidate(
                        "trying to open another tag while one is already opened");
                tagOpened = true;
                continue;
            } else if (c == '\"') {
                if (!tagOpened)
                    return this->invalidate(
                        "tag must be open to read content: extra quote");
                tagContentOpened = !tagContentOpened;
                continue;
            }
            if (c == ']') {
                if (!tagOpened)
                    return this->invalidate("tag not opened: extra closing ]");
                tagOpened = false;
                this->tags_.emplace_back(tagTitle, tagContent);
                tagContent = "";
                tagTitle = "";
                continue;
            }
            if (tagContentOpened)
                tagContent += c;
            else if (!std::isspace(c))
                tagTitle += c;
        }
    }
    if (tagContentOpened)
        return this->invalidate("tag content non closed, a quote is missing");
    if (tagOpened)
        return this->invalidate("tag not closed");
    if (!tagTitle.empty())
        return this->invalidate("tag title is not empty");
    if (!tagContent.empty())
        return this->invalidate("tag content is not empty");
    for (const auto& rTag : ChessTrainer::Notation::PGN::required_tags_) {
        std::string strTag = rTag;
        if (std::find_if(this->tags_.begin(),
                         this->tags_.end(),
                         [strTag](const tag& t) {
                             std::string tagName = t.first;
                             std::transform(tagName.begin(),
                                            tagName.end(),
                                            tagName.begin(),
                                            [](unsigned char c) {
                                                return std::tolower(c);
                                            });
                             return tagName == strTag;
                         }) == this->tags_.end())
            return this->invalidate(
                "required tag '" + std::string(rTag) + "' is missing");
    }
    return true;
}

bool ChessTrainer::Notation::PGN::invalidate(const std::string& reasons) {
    std::cerr << "Invalid PGN: " << reasons << std::endl;
    this->tags_.clear();
    this->board_.clear();
    this->valid_ = false;
    return false;
}

ChessTrainer::Notation::PGN::PGN(std::string input)
    : board_(IPiece::Color::White) {
    this->readTags(input);

    std::cout << "Tags:" << std::endl;
    for (const auto& t : this->tags_)
        std::cout << "['" << t.first << "' '" << t.second << "']" << std::endl;

}

bool ChessTrainer::Notation::PGN::isValid() const {
    return this->valid_;
}
