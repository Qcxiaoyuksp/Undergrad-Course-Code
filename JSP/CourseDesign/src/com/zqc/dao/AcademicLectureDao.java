package com.zqc.dao;

import com.zqc.entity.AcademicLecture;

import java.util.List;

public interface AcademicLectureDao {
    public List<AcademicLecture> list();
    public List<AcademicLecture> search(String key,String value);
    public Integer save(AcademicLecture academicLecture);
    public Integer update(AcademicLecture academicLecture);
    public Integer delete(Integer id);
}
