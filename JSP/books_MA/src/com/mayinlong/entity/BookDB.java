package com.mayinlong.entity;
public class BookDB {

	private Integer bid;// 主键ID
	private String bookName;// 论文名称
	private String author;// 作者
	private Integer num;// 库存
	private String press;// 出版社
	private Integer tid;// 类别ID
	private String typeName;// 类别名称
	private Integer times;// 被借阅次数
	private String part;// 类别名称
	private String digest;// 类别名称
	private String code;// 类别名称
	private String grade;// 类别名称
	private String shoulu;// 类别名称
	private String project;// 类别名称
	
	
	
	
	public String getbookName() {
		return bookName;
	}
	public void setbookName(String bookName) {
		this.bookName = bookName;
	}
	public String getPart() {
		return part;
	}
	public void setPart(String part) {
		this.part = part;
	}
	public String getDigest() {
		return digest;
	}
	public void setDigest(String digest) {
		this.digest = digest;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	public String getGrade() {
		return grade;
	}
	public void setGrade(String grade) {
		this.grade = grade;
	}
	public String getShoulu() {
		return shoulu;
	}
	public void setShoulu(String shoulu) {
		this.shoulu = shoulu;
	}
	public String getProject() {
		return project;
	}
	public void setProject(String project) {
		this.project = project;
	}
	public Integer getBid() {
		return bid;
	}
	public void setBid(Integer bid) {
		this.bid = bid;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public Integer getNum() {
		return num;
	}
	public void setNum(Integer num) {
		this.num = num;
	}
	public String getPress() {
		return press;
	}
	public void setPress(String press) {
		this.press = press;
	}
	public Integer getTid() {
		return tid;
	}
	public void setTid(Integer tid) {
		this.tid = tid;
	}
	public String getTypeName() {
		return typeName;
	}
	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}
	public Integer getTimes() {
		return times;
	}
	public void setTimes(Integer times) {
		this.times = times;
	}
	@Override
	public String toString() {
		return "BookDB [bid=" + bid + ", bookName=" + bookName + ", author=" + author + ", num=" + num + ", press="
				+ press + ", tid=" + tid + ", typeName=" + typeName + ", times=" + times + ", part=" + part
				+ ", digest=" + digest + ", code=" + code + ", grade=" + grade + ", shoulu=" + shoulu + ", project="
				+ project + "]";
	}
	
	
	
}
