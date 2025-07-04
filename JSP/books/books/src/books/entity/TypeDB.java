package books.entity;
/**
 * 图书类别实体
 * @author Administrator
 *
 */
public class TypeDB {

	private Integer tid;
	private String typeName;
	
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
	
	@Override
	public String toString() {
		return "TypeDB [tid=" + tid + ", typeName=" + typeName + "]";
	}
	
}
