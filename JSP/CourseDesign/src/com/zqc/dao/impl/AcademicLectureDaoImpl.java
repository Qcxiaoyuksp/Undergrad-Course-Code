package com.zqc.dao.impl;

import com.zqc.dao.AcademicLectureDao;
import com.zqc.entity.AcademicLecture;
import com.zqc.entity.SystemAdmin;
import com.zqc.util.JDBCUtil;

import java.sql.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class AcademicLectureDaoImpl implements AcademicLectureDao {
    @Override
    public List<AcademicLecture> list() {
        Connection connection = JDBCUtil.getConnection();
        String sql = "select * from lecture";
        PreparedStatement statement = null;
        ResultSet resultSet = null;
        List<AcademicLecture> list = new ArrayList<>();
        try {
            statement = connection.prepareStatement(sql);
            resultSet = statement.executeQuery();
            while (resultSet.next()) {
                int id = resultSet.getInt(1);
                String title = resultSet.getString(2);
                String summary = resultSet.getString(3);
                String department_undertake = resultSet.getString(4);
                String speaker = resultSet.getString(5);
                String department_speaker = resultSet.getString(6);
                String title_speaker = resultSet.getString(7);
                String inviter = resultSet.getString(8);
                String number_participants = resultSet.getString(9);
                String data_lecture = resultSet.getString(10);
                String time = resultSet.getString(11);
                String address = resultSet.getString(12);
                list.add(new AcademicLecture(id,title,summary,department_undertake,speaker,department_speaker,title_speaker,inviter,number_participants,data_lecture,time,address));

            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, resultSet);
        }
        return list;
    }

    @Override
    public List<AcademicLecture> search(String key, String value) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "select * from lecture where "+key+" like '%"+value+"%'";
        PreparedStatement statement = null;
        ResultSet resultSet = null;
        List<AcademicLecture> list = new ArrayList<>();
        try {
            statement = connection.prepareStatement(sql);
            // statement.setString(1,key);
            // statement.setString(2,value);
            resultSet = statement.executeQuery();
            while (resultSet.next()) {
                int id = resultSet.getInt(1);
                String title = resultSet.getString(2);
                String summary = resultSet.getString(3);
                String department_undertake = resultSet.getString(4);
                String speaker = resultSet.getString(5);
                String department_speaker = resultSet.getString(6);
                String title_speaker = resultSet.getString(7);
                String inviter = resultSet.getString(8);
                String number_participants = resultSet.getString(9);
                String data_lecture = resultSet.getString(10);
                String time = resultSet.getString(11);
                String address = resultSet.getString(12);
                list.add(new AcademicLecture(id,title,summary,department_undertake,speaker,department_speaker,title_speaker,inviter,number_participants,data_lecture,time,address));

            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, resultSet);
        }
        return list;
    }

    @Override
    public Integer save(AcademicLecture academicLecture) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "insert into lecture(title,department_undertake,speaker,department_speaker,title_speaker,data_lecture,time,address) values(?,?,?,?,?,?,?,?)";
        PreparedStatement statement = null;
        Integer result = null;
        try {
            statement = connection.prepareStatement(sql);
            statement.setString(1,academicLecture.getTitle());
            statement.setString(2,academicLecture.getDepartment_undertake());
            statement.setString(3,academicLecture.getSpeaker());
            statement.setString(4,academicLecture.getDepartment_speaker());
            statement.setString(5,academicLecture.getTitle_speaker());
            statement.setString(6,academicLecture.getData_lecture());
            statement.setString(7,academicLecture.getTime());
            statement.setString(8,academicLecture.getAddress());
            result = statement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, null);
        }
        return result;
    }

    @Override
    public Integer update(AcademicLecture academicLecture) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "update lecture set title=?,department_undertake=?,speaker=?,department_speaker=?,title_speaker=?,data_lecture=?,time=?,address=? where id = ?";
        PreparedStatement statement = null;
        Integer result = null;
        try {
            statement = connection.prepareStatement(sql);
            statement.setString(1,academicLecture.getTitle());
            statement.setString(2,academicLecture.getDepartment_undertake());
            statement.setString(3,academicLecture.getSpeaker());
            statement.setString(4,academicLecture.getDepartment_speaker());
            statement.setString(5,academicLecture.getTitle_speaker());
            statement.setString(6,academicLecture.getData_lecture());
            statement.setString(7,academicLecture.getTime());
            statement.setString(8,academicLecture.getAddress());
            statement.setInt(9,academicLecture.getId());
            result = statement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, null);
        }
        return result;
    }

    @Override
    public Integer delete(Integer id) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "delete from lecture where id = " + id;
        PreparedStatement statement = null;
        Integer result = null;
        try {
            statement = connection.prepareStatement(sql);
            result = statement.executeUpdate();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, null);
        }
        return result;
    }
}
