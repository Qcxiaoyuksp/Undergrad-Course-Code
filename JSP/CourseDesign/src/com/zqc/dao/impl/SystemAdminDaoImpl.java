package com.zqc.dao.impl;

import com.zqc.dao.SystemAdminDao;
import com.zqc.entity.SystemAdmin;
import com.zqc.util.JDBCUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SystemAdminDaoImpl implements SystemAdminDao {
    @Override
    public SystemAdmin findByUserID(String userID) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "select * from user where userID = '"+userID+"'";
        PreparedStatement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.prepareStatement(sql);
            resultSet = statement.executeQuery();
            if (resultSet.next()) {
                int id = resultSet.getInt(1);
                userID = resultSet.getString(2);
                String password = resultSet.getString(3);
                String name = resultSet.getString(4);
                String gender = resultSet.getString(5);
                String birth_data = resultSet.getString(6);
                String nation = resultSet.getString(7);
                String department = resultSet.getString(8);
                String address = resultSet.getString(9);
                String phone_work = resultSet.getString(10);
                String phone_home = resultSet.getString(11);
                String email = resultSet.getString(12);
                String education = resultSet.getString(13);
                String degree = resultSet.getString(14);
                String title = resultSet.getString(15);
                String major = resultSet.getString(16);
                String graduation_university = resultSet.getString(17);
                String graduation_data = resultSet.getString(18);

                return new SystemAdmin(id,userID,password,name,gender,birth_data,nation,department,address,phone_work,phone_home,email,education,degree,title,major,graduation_university,graduation_data);
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, resultSet);
        }
        return null;
    }

    @Override
    public Integer register(SystemAdmin systemAdmin) {
        Connection connection = JDBCUtil.getConnection();
        String sql = "insert into user(name,gender,nation,birth_date,education,degree,title,major,graduation_university,graduation_date,department,address,phone_work,phone_home,email,userID,password) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
        PreparedStatement statement = null;
        Integer result = null;
        try {
            statement = connection.prepareStatement(sql);
            statement.setString(1,systemAdmin.getName());
            statement.setString(2,systemAdmin.getGender());
            statement.setString(3,systemAdmin.getNation());
            statement.setString(4,systemAdmin.getBirth_data());
            statement.setString(5,systemAdmin.getEducation());
            statement.setString(6,systemAdmin.getDegree());
            statement.setString(7,systemAdmin.getTitle());
            statement.setString(8,systemAdmin.getMajor());
            statement.setString(9,systemAdmin.getGraduation_university());
            statement.setString(10,systemAdmin.getGraduation_data());
            statement.setString(11,systemAdmin.getDepartment());
            statement.setString(12,systemAdmin.getAddress());
            statement.setString(13,systemAdmin.getPhone_work());
            statement.setString(14,systemAdmin.getPhone_home());
            statement.setString(15,systemAdmin.getEmail());
            statement.setString(16,systemAdmin.getUserID());
            statement.setString(17,systemAdmin.getPassword());

            result = statement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            JDBCUtil.release(connection, statement, null);
        }
        return result;
    }
}
