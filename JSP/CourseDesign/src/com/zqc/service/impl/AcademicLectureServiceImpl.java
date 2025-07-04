package com.zqc.service.impl;

import com.zqc.dao.AcademicLectureDao;
import com.zqc.dao.impl.AcademicLectureDaoImpl;
import com.zqc.entity.AcademicLecture;
import com.zqc.service.AcademicLectureService;

import java.util.List;

public class AcademicLectureServiceImpl implements AcademicLectureService {
    private AcademicLectureDao academicLectureDao = new AcademicLectureDaoImpl();
    @Override
    public List<AcademicLecture> list() {
        return this.academicLectureDao.list();
    }

    @Override
    public List<AcademicLecture> search(String key, String value) {
        if(value.equals("")) return this.academicLectureDao.list();
        return this.academicLectureDao.search(key, value);
    }

    @Override
    public void save(AcademicLecture academicLecture) {
        Integer save = this.academicLectureDao.save(academicLecture);
        if (save != 1) throw new RuntimeException("学术讲座信息添加失败");
    }

    @Override
    public void update(AcademicLecture academicLecture) {
        Integer update = this.academicLectureDao.update(academicLecture);
        if (update != 1) throw new RuntimeException("学术讲座信息更新失败");
    }

    @Override
    public void delete(Integer id) {
        Integer delete = this.academicLectureDao.delete(id);
        if (delete != 1) throw new RuntimeException("学术讲座信息删除失败");
    }
}
