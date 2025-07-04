package com.zqc.entity;

public class SystemAdmin {
    private Integer id;
    private String userID;
    private String password;
    private String name;
    private String gender;
    private String birth_data;
    private String nation;
    private String department;
    private String address;
    private String phone_work;
    private String phone_home;
    private String email;
    private String education;
    private String degree;
    private String title;
    private String major;
    private String graduation_university;
    private String graduation_data;

    public SystemAdmin(String userID, String password, String name, String gender, String birth_data, String nation, String department, String address, String phone_work, String phone_home, String email, String education, String degree, String title, String major, String graduation_university, String graduation_data) {
        this.userID = userID;
        this.password = password;
        this.name = name;
        this.gender = gender;
        this.birth_data = birth_data;
        this.nation = nation;
        this.department = department;
        this.address = address;
        this.phone_work = phone_work;
        this.phone_home = phone_home;
        this.email = email;
        this.education = education;
        this.degree = degree;
        this.title = title;
        this.major = major;
        this.graduation_university = graduation_university;
        this.graduation_data = graduation_data;
    }

    public SystemAdmin(Integer id, String userID, String password, String name, String gender, String birth_data, String nation, String department, String address, String phone_work, String phone_home, String email, String education, String degree, String title, String major, String graduation_university, String graduation_data) {
        this.id = id;
        this.userID = userID;
        this.password = password;
        this.name = name;
        this.gender = gender;
        this.birth_data = birth_data;
        this.nation = nation;
        this.department = department;
        this.address = address;
        this.phone_work = phone_work;
        this.phone_home = phone_home;
        this.email = email;
        this.education = education;
        this.degree = degree;
        this.title = title;
        this.major = major;
        this.graduation_university = graduation_university;
        this.graduation_data = graduation_data;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getBirth_data() {
        return birth_data;
    }

    public void setBirth_data(String birth_data) {
        this.birth_data = birth_data;
    }

    public String getNation() {
        return nation;
    }

    public void setNation(String nation) {
        this.nation = nation;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getPhone_work() {
        return phone_work;
    }

    public void setPhone_work(String phone_work) {
        this.phone_work = phone_work;
    }

    public String getPhone_home() {
        return phone_home;
    }

    public void setPhone_home(String phone_home) {
        this.phone_home = phone_home;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEducation() {
        return education;
    }

    public void setEducation(String education) {
        this.education = education;
    }

    public String getDegree() {
        return degree;
    }

    public void setDegree(String degree) {
        this.degree = degree;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getMajor() {
        return major;
    }

    public void setMajor(String major) {
        this.major = major;
    }

    public String getGraduation_university() {
        return graduation_university;
    }

    public void setGraduation_university(String graduation_university) {
        this.graduation_university = graduation_university;
    }

    public String getGraduation_data() {
        return graduation_data;
    }

    public void setGraduation_data(String graduation_data) {
        this.graduation_data = graduation_data;
    }
}
