#pragma once
#include "db_manager.hpp"
#include "medical_examination.hpp"
#include <optional>
#include <vector>

class MedicalExaminationRepository
{
  public:
    explicit MedicalExaminationRepository(DBManager& db);

    std::vector<MedicalExamination>   get_all();
    std::optional<MedicalExamination> get_by_id(int id);
    void                              insert(const MedicalExamination& e);
    void                              update(const int id, const MedicalExamination& e);
    void                              remove(int id);

  private:
    DBManager& db_;
};
