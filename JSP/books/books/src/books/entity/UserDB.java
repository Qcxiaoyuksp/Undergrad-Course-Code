package books.entity;

/*
 * 用户的实体类
 * */
public class UserDB {
	
	private Integer uid; //id
	private String account; //账号
	private String password; //密码
	private String name;//姓名
	private String phone;//电话
	private Integer times;//可借阅数量
	private Integer lendNum; //可借阅天数
	private Integer maxNum; //最大可借数量
	private Integer role; //角色 1: 用户 2 :管理员
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
	public Integer getLendNum() {
		return lendNum;
	}
	public void setLendNum(Integer lendNum) {
		this.lendNum = lendNum;
	}
	public Integer getMaxNum() {
		return maxNum;
	}
	public void setMaxNum(Integer maxNum) {
		this.maxNum = maxNum;
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
				+ phone + ", times=" + times + ", lendNum=" + lendNum + ", maxNum=" + maxNum + ", role=" + role + "]";
	}
	
	

}
