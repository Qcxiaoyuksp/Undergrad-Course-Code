package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.mapper.StatementMapper;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;
import java.util.Date;
import java.util.List;

@Service
public class StatementServiceImpl implements IStatementService {
    @Autowired
    private StatementMapper mapper;

    @Override
    public void insert(Statement statement) {
        statement.setCreateTime(new Date());
        mapper.insert(statement);
    }

    @Override
    public void update(Statement statement) {
        mapper.updateByPrimaryKey(statement);
    }

    @Override
    public void delete(Long id) {
        mapper.deleteByPrimaryKey(id);
    }

    @Override
    public Statement get(Long id) {
        return mapper.selectByPrimaryKey(id);
    }

    @Override
    public void updateAmount(Long statementId, BigDecimal totalAmount, BigDecimal totalQuantity,
                             BigDecimal disCountPrice) {
        Statement statement = new Statement();
        statement.setId(statementId);
        statement.setTotalAmount(totalAmount);
        statement.setTotalQuantity(totalQuantity);
        statement.setDiscountAmount(disCountPrice);
        mapper.update(statement);
    }

    @Override
    public void remove(Long[] id) {
        if (id != null || id.length > 0){
            for (Long i : id) {
                Statement statement = this.get(i);
                //只有消费中中才能修改
                if (Statement.STATUS_CONSUME.equals(statement.getStatus())){
                    mapper.deleteByPrimaryKey(i);
                }
            }
        }
    }

    @Override
    public void edit(Statement statement) {
        //只有消费中才能修改
        if (!Statement.STATUS_CONSUME.equals(statement.getStatus())){
            throw new BusinessException("只有消费中的服务才可以修改");
        }
        mapper.updateByPrimaryKey(statement);
    }

    @Override
    public TablePageInfo<Statement> selectForList(StatementQuery qo) {
        //使用分页框架实现分页功能PageHelper
        PageHelper.startPage(qo.getPageNum(),qo.getPageSize());
        TablePageInfo<Statement> tablePageInfo = new TablePageInfo<>(mapper.selectForList(qo));
        return tablePageInfo;
    }

    @Override
    public List<Statement> listAll() {
        return mapper.selectAll();
    }
}
