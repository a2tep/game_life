#include "game_model.h"
// преобразует строку правила в массив bool (например "23" → [F,F,T,T,F,F,F,F,F])
std::vector<bool> Game_model::ruleToBool(const std::string &rule) {
    std::vector<bool> new_rule(9, false);
    for (const auto &i: rule) {
        new_rule[i - '0'] = true;
    }
    return new_rule;
}
//считаем живых
int Game_model::neighbors(const Field &field, int size, int row, int column) {
    int count = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i != 0 || j != 0) {
                int n_row = Field::normalize(row + i, size);
                int n_column = Field::normalize(column + j, size);
                if (field.getState(n_row, n_column)) {
                    ++count;
                }
            }
        }
    }
    return count;
}


Game_model::Game_model(): Game_model(
        Default_name,
        Default_b_rule,
        Default_s_rule,
        Default_frame
) {}
//правила (txt файл)
Game_model::Game_model(
        const std::string& name,
        const std::string& brule,
        const std::string& srule,
        const std::vector<Point>& coords
):
        name(name),
        b_rule(ruleToBool(brule)),
        s_rule(ruleToBool(srule)),
        field_1(coords)
{}
//поле имя номер итерации

const Field& Game_model::getField() const {
    return current_field == 1? field_1: field_2;
}

const std::string& Game_model::getName() const {
    return name;
}

int Game_model::getGlobIteration() const {
    return global_iteration;
}
//итерация
void Game_model::computeIteration() {
    auto source_field = current_field == 1? &field_1: &field_2;
    auto target_field = current_field == 1? &field_2: &field_1;
    for (int i = 0; i < field_1.getSize(); ++i) {
        for (int j = 0; j < field_1.getSize(); ++j) {
            target_field->setState(i, j, false);
            int count_neigh = neighbors(*source_field, source_field->getSize(), i, j);
            if (source_field->getState(i, j) && s_rule[count_neigh]) {
                target_field->setState(i, j, true);
            } else if (!source_field->getState(i, j) && b_rule[count_neigh]) {
                target_field->setState(i, j, true);
            }
        }
    }
    current_field = current_field == 1? 2: 1;
    ++global_iteration;
}
