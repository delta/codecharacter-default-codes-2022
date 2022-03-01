public class Position implements Comparable<Position> {
    private final int _x;
    private final int _y;

    public Position(int x, int y) {
        _x = x;
        _y = y;
    }

    public int getX() {
        return _x;
    }

    public int getY() {
        return _y;
    }

    public double distanceTo(Position other) {
        return Math.sqrt(Math.pow(other.getX() - _x, 2) + Math.pow(other.getY() - _y, 2));
    }

    @Override
    public int compareTo(Position o) {
        // Compare by x, then by y
        if (_x != o._x) {
            return _x - o._x;
        } else {
            return _y - o._y;
        }
    }

    @Override
    public String toString() {
        return "Position [_x=" + _x + ", _y=" + _y + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + _x;
        result = prime * result + _y;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Position other = (Position) obj;
        if (_x != other._x)
            return false;
        if (_y != other._y)
            return false;
        return true;
    }
}
