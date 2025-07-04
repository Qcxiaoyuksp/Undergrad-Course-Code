package com.zqc.service;

import com.zqc.entity.AcademicLecture;

import java.util.List;

public interface AcademicLectureService {
    public List<AcademicLecture> list();
    public List<AcademicLecture> search(String key, String value);
    public void save(AcademicLecture academicLecture);
    public void update(AcademicLecture academicLecture);
    public void delete(Integer id);
}
