package com.zqc.entity;

import java.sql.Time;
import java.util.Date;

public class AcademicLecture {
    private Integer id;
    private String title;
    private String summary;
    private String department_undertake;
    private String speaker;
    private String department_speaker;
    private String title_speaker;
    private String inviter;
    private String number_participants;
    private String data_lecture;
    private String time;
    private String address;

    public AcademicLecture(Integer id, String title, String department_undertake, String speaker, String department_speaker, String title_speaker, String data_lecture, String time, String address) {
        this.id = id;
        this.title = title;
        this.department_undertake = department_undertake;
        this.speaker = speaker;
        this.department_speaker = department_speaker;
        this.title_speaker = title_speaker;
        this.data_lecture = data_lecture;
        this.time = time;
        this.address = address;
    }

    public AcademicLecture(String title, String department_undertake, String speaker, String department_speaker, String title_speaker, String data_lecture, String time, String address) {
        this.title = title;
        this.department_undertake = department_undertake;
        this.speaker = speaker;
        this.department_speaker = department_speaker;
        this.title_speaker = title_speaker;
        this.data_lecture = data_lecture;
        this.time = time;
        this.address = address;
    }

    public AcademicLecture(Integer id, String title, String summary, String department_undertake, String speaker, String department_speaker, String title_speaker, String inviter, String number_participants, String data_lecture, String time, String address) {
        this.id = id;
        this.title = title;
        this.summary = summary;
        this.department_undertake = department_undertake;
        this.speaker = speaker;
        this.department_speaker = department_speaker;
        this.title_speaker = title_speaker;
        this.inviter = inviter;
        this.number_participants = number_participants;
        this.data_lecture = data_lecture;
        this.time = time;
        this.address = address;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getSummary() {
        return summary;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getDepartment_undertake() {
        return department_undertake;
    }

    public void setDepartment_undertake(String department_undertake) {
        this.department_undertake = department_undertake;
    }

    public String getSpeaker() {
        return speaker;
    }

    public void setSpeaker(String speaker) {
        this.speaker = speaker;
    }

    public String getDepartment_speaker() {
        return department_speaker;
    }

    public void setDepartment_speaker(String department_speaker) {
        this.department_speaker = department_speaker;
    }

    public String getTitle_speaker() {
        return title_speaker;
    }

    public void setTitle_speaker(String title_speaker) {
        this.title_speaker = title_speaker;
    }

    public String getInviter() {
        return inviter;
    }

    public void setInviter(String inviter) {
        this.inviter = inviter;
    }

    public String getNumber_participants() {
        return number_participants;
    }

    public void setNumber_participants(String number_participants) {
        this.number_participants = number_participants;
    }

    public String getData_lecture() {
        return data_lecture;
    }

    public void setData_lecture(String data_lecture) {
        this.data_lecture = data_lecture;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
