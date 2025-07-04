package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.domain.StatementItem;
import cn.wolfcode.car.business.mapper.StatementItemMapper;
import cn.wolfcode.car.business.mapper.StatementMapper;
import cn.wolfcode.car.business.query.StatementItemQuery;
import cn.wolfcode.car.business.service.IStatementItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.List;

@Service
@Transactional
public class StatementItemServiceImpl implements IStatementItemService {

    @Autowired
    private StatementItemMapper StatementItemMapper;
    @Autowired
    private StatementMapper statementMapper;


    @Override
    public TablePageInfo<StatementItem> query(StatementItemQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());
        return new TablePageInfo<StatementItem>(StatementItemMapper.selectForList(qo));
    }


    @Override
    public void save(StatementItem statementItem) {
        // 从安全角度考虑，前台传递过来的对象是不可以直接使用的。
        // 所以我们都新建对象。这样无论如何都不会因为前台传递了默认值而改变我们的默认值数据。

        StatementItemMapper.insert(statementItem);
    }

    @Override
    public StatementItem get(Long id) {
        return StatementItemMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(StatementItem statementItem) {

        StatementItemMapper.updateByPrimaryKey(statementItem);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            StatementItemMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public List<StatementItem> list() {
        return StatementItemMapper.selectAll();
    }

    @Override
    @Transactional
    public void saveItems(List<StatementItem> list) {
        if(list != null && list.size() > 0 ){
            // 取出最后一条数据，获取我们的额外参数信息
            StatementItem temp = list.remove(list.size() - 1);
            // 获取到 StatementId 结算单 id
            Long statementId = temp.getStatementId();
            // 获取到 discountAmount 优惠价格
            // 状态必须处于消费中才能进行保存明细操作。
            Statement statement = statementMapper.selectByPrimaryKey(statementId);
            if(Statement.STATUS_PAID.equals(statement.getStatus())){
                throw new BusinessException("已支付的结算单不能进行保存操作");
            }
            // 由于不确定是否之前已经存在数据（是否是之前已经保存过在修改了）。所以我们采用先删后加
            StatementItemMapper.deleteRealtionBatchByStatementId(statement.getId());
            // 保存结算单明细
            StatementItemMapper.insertRelationBatch(list);
            //
            BigDecimal totalAmount = new BigDecimal("0.00");        // 总金额
            BigDecimal totalQuantity = new BigDecimal("0");         // 总数量
            BigDecimal discountAmount = temp.getItemPrice();            // 折扣金额
            for(StatementItem statementItem : list){
                // 计算总金额 = 单价 * 数量
                totalAmount = totalAmount.add(statementItem.getItemPrice().multiply(statementItem.getItemQuantity()));
                // 计算总数量  累加
                totalQuantity = totalQuantity.add(statementItem.getItemQuantity());
            }
            if(discountAmount == null || discountAmount.compareTo(new BigDecimal(0)) < 0){
                throw new BusinessException("优惠金额不能小于0");
            }
            if(discountAmount.compareTo(totalAmount) > 0){
                throw new BusinessException("优惠金额不能大于总金额");
            }
            // 更新结算单信息
            statement.setTotalAmount(totalAmount);
            statement.setTotalQuantity(totalQuantity);
            statement.setDiscountAmount(discountAmount);
            statementMapper.updateByStatementItem(statement);
        }
    }
}
