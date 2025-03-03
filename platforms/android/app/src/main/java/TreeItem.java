import android.util.Log;

import com.example.note2.TreeNode;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;

public class TreeItem {
    private static final String TAG = "TreeItem";

    private int defaultColumn;
    // For simplicity, we store the top-level items (years) in a list.
    private List<TreeNode> yearItems;
    // If you have a custom tree view widget, you might hold a reference here.
    private Object treeWidget;

    public TreeItem(Object treeWidget, int defaultColumn) {
        this.defaultColumn = defaultColumn;
        this.treeWidget = treeWidget;
        this.yearItems = new ArrayList<>();
        // You might configure your treeWidget here if needed.
    }

    // Searches for an element in a list of TreeNodes that has matching text.
    public int isExistElementInList(List<TreeNode> items, String keyword) {
        for (int i = 0; i < items.size(); i++) {
            if (items.get(i).getText().equals(keyword)) {
                return i;
            }
        }
        Log.w(TAG, "WARNING: isExistElement not found");
        return -1;
    }

    // Searches for a child element of a given TreeNode with matching text.
    public int isExistChildInElement(TreeNode item, String keyword) {
        List<TreeNode> children = item.getChildren();
        for (int i = 0; i < children.size(); i++) {
            if (children.get(i).getText().equals(keyword)) {
                return i;
            }
        }
        return -1;
    }

    // Sorts the children of a given TreeNode numerically based on the text.
    public int sortChildrenOfItem(TreeNode item) {
        List<TreeNode> children = item.getChildren();
        Collections.sort(children, new Comparator<TreeNode>() {
            @Override
            public int compare(TreeNode o1, TreeNode o2) {
                try {
                    int i1 = Integer.parseInt(o1.getText());
                    int i2 = Integer.parseInt(o2.getText());
                    return Integer.compare(i1, i2);
                } catch (NumberFormatException e) {
                    return o1.getText().compareTo(o2.getText());
                }
            }
        });
        return 0;
    }

    // Appends a new child element with the given text to a TreeNode, but only if it does not already exist.
    public int appendOnceElement(TreeNode item, String text) {
        int index = isExistChildInElement(item, text);
        if (index == -1) {
            index = item.getChildren().size();
            TreeNode newNode = new TreeNode(text);
            item.getChildren().add(index, newNode);
        }
        return index;
    }

    // Appends a new date to the tree. The date is provided as three strings: year, month, and day.
    public int appendNewDate(String year, String month, String day) {
        int yearIndex = isExistElementInList(yearItems, year);
        if (yearIndex == -1) {
            TreeNode yearNode = new TreeNode(year);
            yearIndex = yearItems.size();
            yearItems.add(yearNode);
        }
        TreeNode yearNode = yearItems.get(yearIndex);
        int monthIndex = appendOnceElement(yearNode, month);
        TreeNode monthNode = yearNode.getChildren().get(monthIndex);
        int dayIndex = appendOnceElement(monthNode, day);
        return 0;
    }

    // Fills the tree using a list of Date objects.
    public int fillTreeByDateList(List<Date> dateList) {
        if (dateList.isEmpty()) {
            throw new AssertionError("dateList must contain at least one element");
        }
        for (Date date : dateList) {
            Calendar cal = Calendar.getInstance();
            cal.setTime(date);
            int year = cal.get(Calendar.YEAR);
            int month = cal.get(Calendar.MONTH) + 1;  // Calendar.MONTH is zero-based.
            int day = cal.get(Calendar.DAY_OF_MONTH);
            Log.d(TAG, "DEBUG: fillTreeByDateList year:" + year + ", month:" + month + ", day:" + day);
            appendNewDate(String.valueOf(year), String.valueOf(month), String.valueOf(day));
        }
        // In Qt, the yearItems were inserted into a QTreeWidget.
        // In Android, update your adapter/view with the 'yearItems' list as needed.
        return 0;
    }

    // Collects all day-level nodes into the provided list.
    public void getDaysList(List<TreeNode> items) {
        for (TreeNode yearNode : yearItems) {
            if (yearNode == null) continue;
            for (TreeNode monthNode : yearNode.getChildren()) {
                if (monthNode == null) continue;
                for (TreeNode dayNode : monthNode.getChildren()) {
                    if (dayNode == null) continue;
                    items.add(dayNode);
                }
            }
        }
    }

    // Installs a signal (callback) on every month node in the tree.
    // The handler is a functional interface that accepts a TreeNode.
    public int installSignalsForExistedTree(Handler handler) {
        for (TreeNode yearNode : yearItems) {
            if (yearNode == null) continue;
            for (TreeNode monthNode : yearNode.getChildren()) {
                handler.onItem(monthNode);
            }
        }
        return 0;
    }

    // Clears the tree.
    public void clear() {
        for (TreeNode yearNode : yearItems) {
            if (yearNode == null) continue;
            for (TreeNode monthNode : yearNode.getChildren()) {
                monthNode.getChildren().clear();
            }
        }
        yearItems.clear();
    }

    // In Java, there is no destructor; call clear() when needed.
    // Optionally, override finalize() (not recommended) or manage cleanup elsewhere.

    // Getter for the year items (could be used to update an adapter).
    public List<TreeNode> getYearItems() {
        return yearItems;
    }

    // A simple interface to mimic the signal/slot handler for items.
    public interface Handler {
        void onItem(TreeNode item);
    }
}
