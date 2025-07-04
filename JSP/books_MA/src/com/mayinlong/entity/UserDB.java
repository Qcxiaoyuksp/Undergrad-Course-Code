package com.mayinlong.entity;

public class UserDB {
	private Integer uid; //id
	private String account;//账号
	private String password;//密码
	private String name;//姓名
	private String phone;//手机
	private Integer times;//下载量
	private Integer role;//角色 1用户 2管理员
	private  String address ;//地址
	private String graduate;//毕业学校
	private String email;//email
	private Integer age;//AGE
	
	
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public String getGraduate() {
		return graduate;
	}
	public void setGraduate(String graduate) {
		this.graduate = graduate;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public Integer getAge() {
		return age;
	}
	public void setAge(Integer age) {
		this.age = age;
	}
	public Integer getUid() {
		return uid;
	}
	public void setUid(Integer uid) {
		this.uid = uid;
	}
	public String getAccount() {
		return account;
	}
	public void setAccount(String account) {
		this.account = account;
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
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public Integer getTimes() {
		return times;
	}
	public void setTimes(Integer times) {
		this.times = times;
	}
	public Integer getRole() {
		return role;
	}
	public void setRole(Integer role) {
		this.role = role;
	}
	@Override
	public String toString() {
		return "UserDB [uid=" + uid + ", account=" + account + ", password=" + password + ", name=" + name + ", phone="
				+ phone + ", times=" + times + ", role=" + role
				+ ", address=" + address + ", graduate=" + graduate + ", email=" + email + ", age=" + age + "]";
	}
	
	
}
