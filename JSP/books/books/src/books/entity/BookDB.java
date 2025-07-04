package books.entity;

public class BookDB {

	private Integer bid;// 主键ID
	private String bookName;// 图书名称
	private String author;// 作者
	private Integer num;// 库存
	private String press;// 出版社
	private Integer tid;// 类别ID
	private String typeName;// 类别名称
	private Integer times;// 被借阅次数
	
	public Integer getBid() {
		return bid;
	}
	public void setBid(Integer bid) {
		this.bid = bid;
	}
	public String getBookName() {
		return bookName;
	}
	public void setBookName(String bookName) {
		this.bookName = bookName;
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
				+ press + ", tid=" + tid + ", typeName=" + typeName + ", times=" + times + "]";
	}
	
}
